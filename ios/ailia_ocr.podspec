#
# To learn more about a Podspec see http://guides.cocoapods.org/syntax/podspec.html.
# Run `pod lib lint ailia_ocr.podspec` to validate before publishing.
#
Pod::Spec.new do |s|
  s.name             = 'ailia_ocr'
  s.version          = '1.2.1'
  s.summary          = 'ailia OCR for Flutter.'
  s.description      = <<-DESC
ailia OCR for Flutter.
                       DESC
  s.homepage         = 'https://ailia.ai/'
  s.license          = { :file => '../LICENSE' }
  s.author           = { 'ax Inc.' => 'contact@ailia.ai' }
  s.source           = { :path => '.' }
  s.source_files = 'Classes/**/*'
  s.vendored_libraries = '*.a'
  s.libraries = ['ailia_ocr', 'c++']
  s.dependency 'Flutter'
  s.platform = :ios, '11.0'

  # Flutter.framework does not contain a i386 slice.
  s.pod_target_xcconfig = { 'DEFINES_MODULE' => 'YES', 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'i386' }
  s.swift_version = '5.0'
end
