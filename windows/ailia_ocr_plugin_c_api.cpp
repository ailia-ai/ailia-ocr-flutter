#include "include/ailia_ocr/ailia_ocr_plugin_c_api.h"

#include <flutter/plugin_registrar_windows.h>

#include "ailia_ocr_plugin.h"

void AiliaOcrPluginCApiRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  ailia_ocr::AiliaOcrPlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
