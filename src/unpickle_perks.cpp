#include <nlohmann/json.hpp>
#include "unpickle_context.h"
#include "f4se/GameReferences.h"
#include "f4se/GameRTTI.h"
#include "util.h"

void RestorePerks(const Json::Value& perks, UnpickleContext& ctx) {
ctx.log.StartPhase("Restoring Perks");

for (const auto& key : perks.getMemberNames()) {
UInt32 formID = ResolveFormID(key);
BGSPerk* perk = DYNAMIC_CAST(LookupFormByID(formID), TESForm, BGSPerk);
if (!perk) {
ctx.resolver.RecordFailure(key);
ctx.log.Warn("Missing perk: " + key);
continue;
}

int rank = perks[key].asInt();
for (int i = 0; i < rank; ++i) {
if (ctx.IsDryRun()) {
ctx.log.Info("[dryrun] Would apply perk " + key);
} else {
CALL_MEMBER_FN((*g_thePlayer), AddPerk)(perk);
ctx.log.Info("Applied perk " + key);
}
}
ctx.resolver.RecordSuccess(key);
}

ctx.log.Done();
}
