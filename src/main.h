#pragma once
#include "f4se/PluginAPI.h"

extern "C" {
    bool F4SEPlugin_Query(const F4SEInterface* f4se, PluginInfo* info);
    bool F4SEPlugin_Load(const F4SEInterface* f4se);
}
