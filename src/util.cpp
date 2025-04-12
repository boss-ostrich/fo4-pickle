#include "util.h"
#include "f4se/GameData.h"
#include <iomanip>
#include <sstream>
#include <fstream>

std::string FormIDToHex(UInt32 id) {
std::ostringstream oss;
oss << "0x" << std::uppercase << std::hex << std::setw(8) << std::setfill('0') << id;
return oss.str();
}

std::string GetEditorID(TESForm* form) {
if (!form) return "";
const char* id = (*g_dataHandler)->GetFormEditorID(form);
return id ? std::string(id) : "";
}

std::string EncodeFormID(UInt32 id, bool includeMod) {
if (!includeMod) return FormIDToHex(id);

UInt8 modIndex = (id >> 24) & 0xFF;
UInt32 local = id & 0x00FFFFFF;
const char* modName = (*g_dataHandler)->GetNthLoadedModName(modIndex);
if (!modName) return FormIDToHex(id);

std::ostringstream oss;
oss << modName << "|" << std::uppercase << std::hex << std::setw(6) << std::setfill('0') << local;
return oss.str();
}

UInt32 ResolveFormID(const std::string& key) {
auto pos = key.find('|');
if (pos == std::string::npos) return std::stoul(key, nullptr, 16); // fallback

std::string modName = key.substr(0, pos);
std::string hexID = key.substr(pos + 1);

UInt32 local = std::stoul(hexID, nullptr, 16);
UInt8 index = (*g_dataHandler)->GetLoadedModIndex(modName.c_str());

if (index == 0xFF) return 0;
return (index << 24) | local;
}

void SaveJson(const std::filesystem::path& path, const Json::Value& root) {
Json::StreamWriterBuilder builder;
std::ofstream file(path);
file << Json::writeString(builder, root);
}
