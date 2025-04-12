#include "export_manager.h"

extern "C" {

  bool F4SEPlugin_Query(const F4SEInterface* f4se, PluginInfo* info) {
    info->infoVersion = PluginInfo::kInfoVersion;
    info->name = "FalloutPickle";
    info->version = 28; // v0.2.8
    return true;
  }

  bool F4SEPlugin_Load(const F4SEInterface* f4se) {
    ExportManager::RegisterCommand();
    return true;
  }
}
