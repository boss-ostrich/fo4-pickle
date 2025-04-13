#include "CommandTable.h"
#include <cstring>

CommandInfo* GetConsoleCommand(const char* name) {
	if (!g_consoleCommands || !name) return nullptr;

	for (uint32_t i = 0; i < g_numConsoleCommands; ++i) {
		CommandInfo& cmd = g_consoleCommands[i];
		if (_stricmp(cmd.longName, name) == 0 || _stricmp(cmd.shortName, name) == 0) {
			return &cmd;
		}
	}
	return nullptr;
}