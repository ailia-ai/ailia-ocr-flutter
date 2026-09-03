#ifndef FLUTTER_PLUGIN_AILIA_OCR_PLUGIN_H_
#define FLUTTER_PLUGIN_AILIA_OCR_PLUGIN_H_

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>

#include <memory>

namespace ailia_ocr {

class AiliaOcrPlugin : public flutter::Plugin {
 public:
  static void RegisterWithRegistrar(flutter::PluginRegistrarWindows *registrar);

  AiliaOcrPlugin();

  virtual ~AiliaOcrPlugin();

  // Disallow copy and assign.
  AiliaOcrPlugin(const AiliaOcrPlugin&) = delete;
  AiliaOcrPlugin& operator=(const AiliaOcrPlugin&) = delete;

  // Called when a method is called on this plugin's channel from Dart.
  void HandleMethodCall(
      const flutter::MethodCall<flutter::EncodableValue> &method_call,
      std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
};

}  // namespace ailia_ocr

#endif  // FLUTTER_PLUGIN_AILIA_OCR_PLUGIN_H_
