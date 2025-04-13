#include <nlohmann/json.hpp>
#include "unpickle_context.h"
#include "f4se/GameForms.h"
#include "f4se/GameRTTI.h"
#include "util.h"

void RestoreQuestStages(const Json::Value& quests, UnpickleContext& ctx) {
ctx.log.StartPhase("Restoring Quests");

for (const auto& key : quests.getMemberNames()) {
UInt32 formID = ResolveFormID(key);
TESQuest* quest = DYNAMIC_CAST(LookupFormByID(formID), TESForm, TESQuest);
if (!quest) {
ctx.log.Warn("Missing quest: " + key);
ctx.resolver.RecordFailure(key);
continue;
}

ctx.resolver.RecordSuccess(key);
for (const auto& s : quests[key]) {
int stage = s.asInt();
if (ctx.IsDryRun()) {
ctx.log.Info("[dryrun] Would set stage " + std::to_string(stage) + " for " + key);
} else {
quest->SetStage(stage);
ctx.log.Info("Set stage " + std::to_string(stage) + " for " + key);
}
}
}

ctx.log.Done();
}
