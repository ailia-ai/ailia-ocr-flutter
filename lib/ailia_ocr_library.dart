import 'dart:convert';
import 'dart:ffi';
import 'dart:io';

/// ailia OCR のネイティブライブラリのファイル名
String ailiaOcrLibraryName() {
  if (Platform.isAndroid || Platform.isLinux) {
    return 'libailia_ocr.so';
  }
  if (Platform.isMacOS) {
    return 'libailia_ocr.dylib';
  }
  if (Platform.isWindows) {
    return 'ailia_ocr.dll';
  }
  return 'internal';
}

/// ailia OCR のネイティブライブラリを開く
///
/// アプリにバンドルされたライブラリをファイル名で開く。`flutter test` や `dart run` の
/// ようにバンドルされていない環境では、`.dart_tool/package_config.json` から本パッケージの
/// 配置先を求め、パッケージ内のライブラリを開く。
DynamicLibrary openAiliaOcrLibrary() {
  if (Platform.isIOS) {
    return DynamicLibrary.process();
  }
  final String name = ailiaOcrLibraryName();
  try {
    return DynamicLibrary.open(name);
  } on ArgumentError {
    final String? path = _packagedLibraryPath(name);
    if (path == null) {
      rethrow;
    }
    return DynamicLibrary.open(path);
  }
}

String? _packagedLibraryPath(String name) {
  final String? root = _packageRoot();
  if (root == null) {
    return null;
  }
  final String dir;
  if (Platform.isMacOS) {
    dir = 'macos';
  } else if (Platform.isLinux) {
    dir = 'linux/x64';
  } else if (Platform.isWindows) {
    dir = Abi.current() == Abi.windowsArm64 ? 'windows/arm64' : 'windows/x64';
  } else {
    return null;
  }
  return '$root/$dir/$name';
}

// カレントディレクトリから親方向に .dart_tool/package_config.json を探し、
// 本パッケージの rootUri を絶対パスで返す
String? _packageRoot() {
  Directory dir = Directory.current;
  for (int i = 0; i < 4; i++) {
    final File file = File('${dir.path}/.dart_tool/package_config.json');
    if (file.existsSync()) {
      final Map<String, dynamic> config =
          jsonDecode(file.readAsStringSync()) as Map<String, dynamic>;
      for (final dynamic package in config['packages'] as List<dynamic>) {
        if (package['name'] == 'ailia_ocr') {
          final Uri rootUri =
              file.absolute.parent.uri.resolve(package['rootUri'] as String);
          String path = rootUri.toFilePath();
          if (path.endsWith(Platform.pathSeparator)) {
            path = path.substring(0, path.length - 1);
          }
          return path;
        }
      }
      return null;
    }
    final Directory parent = dir.parent;
    if (parent.path == dir.path) {
      break;
    }
    dir = parent;
  }
  return null;
}
