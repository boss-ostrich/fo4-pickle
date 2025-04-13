#include <nlohmann/json.hpp>
#include "PickleContext.h"
#include "f4se/GameForms.h"
#include "f4se/GameData.h"
#include "util.h"

void WriteGlobals(PickleContext& ctx) {
Json::Value root;
int count = 0;

for (UInt32 i = 0; i < (*g_dataHandler)->arrTESForm[FormType::kFormType_Global].count; ++i) {
TESGlobal* g = DYNAMIC_CAST((*g_dataHandler)->arrTESForm[FormType::kFormType_Global].entries[i], TESForm, TESGlobal);
if (g && g->value != 0.0f) {
root[ModKeyForFormID(g->formID)] = g->value;
count++;
}
}

ctx.SaveJson("Globals.json", root);
ctx.Log("Globals: " + std::to_string(count));
ctx.verboseLog.Info("Exported " + std::to_string(count) + " global variables");
}
