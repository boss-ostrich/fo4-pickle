#pragma once

#include <cstdint>

struct CommandInfo {
	const char* longName;
	const char* shortName;
	uint16_t opcode;
	const char* helpText;
	uint8_t needsParent;
	uint8_t isRefRequired;
	void* execute;  // Typing as void* for now to keep it generic
	void* parse;
	void* eval;
	void* unk;
};

extern CommandInfo* g_consoleCommands;
extern uint32_t g_numConsoleCommands;

CommandInfo* GetConsoleCommand(const char* name);