#include "flag_parser.h"
#include "f4se_shims/CommandTable.h"
#include <sstream>

namespace {
std::vector<std::string> GetArgs() {
std::vector<std::string> args;
std::string input = GetConsoleInput();
std::istringstream iss(input);
std::string word;
while (iss >> word) args.push_back(word);
return args;
}
}

bool FlagParser::FlagSet::IsEnabled(const std::string& key) const {
if (excluded.count(key)) return false;
if (included.empty()) return true;
return included.count(key) > 0;
}

FlagParser::FlagSet FlagParser::Parse() {
FlagSet flags;
auto args = GetArgs();

for (const auto& arg : args) {
if (arg == "pickle" || arg == "unpickle") continue;
if (arg.starts_with("path=")) flags.pathOverride = arg.substr(5);
else if (arg.starts_with("out=")) flags.outputPath = arg.substr(4);
else if (arg.starts_with("!")) flags.excluded.insert(arg.substr(1));
else if (arg.starts_with("-")) flags.excluded.insert(arg.substr(1));
else if (arg.starts_with("+")) flags.included.insert(arg.substr(1));
else flags.included.insert(arg);
}
return flags;
}
