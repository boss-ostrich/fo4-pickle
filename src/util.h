#pragma once
#include <string>
#include <filesystem>
#include "f4se/GameForms.h"

std::string FormIDToHex(UInt32 id);
std::string GetEditorID(TESForm* form);
std::string EncodeFormID(UInt32 id, bool includeMod = true);
UInt32 ResolveFormID(const std::string& key);
void SaveJson(const std::filesystem::path& path, const Json::Value& root);
