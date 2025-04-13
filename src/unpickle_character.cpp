#include <nlohmann/json.hpp>
#include "unpickle_context.h"
#include "f4se/GameReferences.h"
#include "f4se/GameForms.h"
#include "util.h"

void ApplyXP(const Json::Value& xpVal, UnpickleContext& ctx) {
ctx.log.StartPhase("Restoring XP");
if (!xpVal.isInt()) {
ctx.log.Warn("Invalid XP value");
ctx.log.Done();
return;
}

int xp = xpVal.asInt();
if (ctx.IsDryRun()) {
ctx.log.Info("[dryrun] Would set XP to " + std::to_string(xp));
} else {
auto av = ActorValueList::GetSingleton()->GetActorValue(0x21);
(*g_thePlayer)->actorValueOwner.SetBase(av, xp);
ctx.log.Info("Set XP to " + std::to_string(xp));
}

ctx.log.Done();
}

void RestoreSPECIAL(const Json::Value& special, UnpickleContext& ctx) {
ctx.log.StartPhase("Restoring SPECIAL");
for (const auto& key : special.getMemberNames()) {
UInt32 formID = ResolveFormID(key);
auto av = ActorValueList::GetSingleton()->GetActorValue(formID);
if (av) {
float val = special[key].asFloat();
if (ctx.IsDryRun()) {
ctx.log.Info("[dryrun] Would set " + key + " to " + std::to_string(val));
} else {
(*g_thePlayer)->actorValueOwner.SetBase(av, val);
ctx.log.Info("Set " + key + " to " + std::to_string(val));
}
ctx.resolver.RecordSuccess(key);
} else {
ctx.resolver.RecordFailure(key);
}
}
ctx.log.Done();
}
