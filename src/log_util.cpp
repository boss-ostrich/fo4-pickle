#include "log_util.h"

#include <fstream>


void LogBuffer::StartPhase(const std::string& name) {
lines.push_back("");
lines.push_back("=== " + name + " ===");
}

void LogBuffer::Info(const std::string& msg) {
lines.push_back("[INFO] " + msg);
}

void LogBuffer::Warn(const std::string& msg) {
lines.push_back("[WARN] " + msg);
}

void LogBuffer::Done() {
lines.push_back("[DONE]");
}

void LogBuffer::Flush(const std::string& path) {
std::ofstream file(path);
for (const auto& line : lines) {
file << line << "\n";
}
}
