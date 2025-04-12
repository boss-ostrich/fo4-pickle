#include "PickleContext.h"
#include "f4se/GameForms.h"
#include "f4se/GameRTTI.h"
#include "util.h"

void WriteQuests(PickleContext& ctx) {
Json::Value root;
int total = 0;

for (UInt32 i = 0; i < (*g_dataHandler)->arrTESForm[FormType::kFormType_Quest].count; ++i) {
TESQuest* quest = DYNAMIC_CAST((*g_dataHandler)->arrTESForm[FormType::kFormType_Quest].entries[i], TESForm, TESQuest);
if (!quest) continue;

Json::Value stages(Json::arrayValue);
for (UInt32 s = 0; s <= 255; s++) {
if (quest->IsStageDone(s)) {
stages.append(Json::Value(s));
}
}

if (!stages.empty()) {
root[ModKeyForFormID(quest->formID)] = stages;
total += stages.size();
}
}

ctx.SaveJson("Quests.json", root);
ctx.Log("Quests: " + std::to_string(total) + " stages");
ctx.verboseLog.Info("Exported quest data for " + std::to_string(root.size()) + " quests");
}
