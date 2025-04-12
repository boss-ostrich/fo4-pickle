#pragma once
#include <string>
#include <unordered_set>
#include <optional>

namespace FlagParser {
struct FlagSet {
std::unordered_set<std::string> included;
std::unordered_set<std::string> excluded;
std::optional<std::string> pathOverride;
std::optional<std::string> outputPath;

bool IsEnabled(const std::string& key) const;
};

FlagSet Parse();
}
