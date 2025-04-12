#pragma once
#include "flag_parser.h"
#include "log_util.h"
#include <filesystem>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace fs = std::filesystem;

struct PickleContext {
std::string characterName;
std::string timestamp;
std::string savegameName;

FlagParser::FlagSet flags;
fs::path exportFolder;
fs::path basePath;

std::vector<std::string> logs;
LogBuffer verboseLog;

void Init(const FlagParser::FlagSet& f);
void Log(const std::string& msg);
void SaveJson(const std::string& filename, const Json::Value& root);
fs::path Path(const std::string& relative) const;
};
