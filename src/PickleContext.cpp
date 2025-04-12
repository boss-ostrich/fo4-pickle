#include "PickleContext.h"
#include "f4se/GameReferences.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <Windows.h>
#include <ShlObj.h>

namespace {
std::string GetCharacterName() {
PlayerCharacter* player = *g_thePlayer;
return player ? CALL_MEMBER_FN(player, GetReferenceName)() : "Unknown";
}

std::string GetTimestamp() {
std::time_t t = std::time(nullptr);
std::tm tm;
localtime_s(&tm, &t);
std::ostringstream oss;
oss << std::put_time(&tm, "%Y-%m-%d_%H-%M-%S");
return oss.str();
}

std::string GetMostRecentSaveFile() {
char docs[MAX_PATH];
if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_MYDOCUMENTS, NULL, 0, docs))) {
fs::path saveDir = fs::path(docs) / "My Games" / "Fallout4" / "Saves";
if (!fs::exists(saveDir)) return "unknown";

std::string latest;
std::time_t latestTime = 0;

for (const auto& entry : fs::directory_iterator(saveDir)) {
if (entry.path().extension() == ".fos") {
auto t = fs::last_write_time(entry);
auto c = decltype(t)::clock::to_time_t(t);
if (c > latestTime) {
latestTime = c;
latest = entry.path().filename().string();
}
}
}
return latest;
}
return "unknown";
}
}

void PickleContext::Init(const FlagParser::FlagSet& f) {
flags = f;
characterName = GetCharacterName();
timestamp = GetTimestamp();
savegameName = GetMostRecentSaveFile();
basePath = flags.outputPath.value_or("Data/Exports");
exportFolder = basePath / (characterName + "_" + timestamp);
fs::create_directories(exportFolder / "Presets");
}

fs::path PickleContext::Path(const std::string& relative) const {
return exportFolder / relative;
}

void PickleContext::Log(const std::string& msg) {
logs.push_back(msg);
}

void PickleContext::SaveJson(const std::string& filename, const Json::Value& root) {
Json::StreamWriterBuilder builder;
std::ofstream file(Path(filename));
file << Json::writeString(builder, root);
Log(filename + " OK");
}
