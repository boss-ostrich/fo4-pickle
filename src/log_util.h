#pragma once
#include <string>
#include <vector>

class LogBuffer {
public:
void StartPhase(const std::string& name);
void Info(const std::string& msg);
void Warn(const std::string& msg);
void Done();
void Flush(const std::string& path);

private:
std::vector<std::string> lines;
};
