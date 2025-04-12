#include "unpickle_context.h"
#include "f4se/GameForms.h"
#include "f4se/GameRTTI.h"
#include "util.h"

void ApplyGlobals(const Json::Value& globals, UnpickleContext& ctx) {
ctx.log.StartPhase("Restoring Globals");

for (const auto& key : globals.getMemberNames()) {
UInt32 formID = ResolveFormID(key);
TESGlobal* g = DYNAMIC_CAST(LookupFormByID(formID), TESForm, TESGlobal);
if (!g) {
ctx.resolver.RecordFailure(key);
ctx.log.Warn("Missing global: " + key);
continue;
}
float val = globals[key].asFloat();

if (ctx.IsDryRun()) {
ctx.log.Info("[dryrun] Would set global " + key + " = " + std::to_string(val));
} else {
g->value = val;
ctx.log.Info("Set global " + key + " = " + std::to_string(val));
}
ctx.resolver.RecordSuccess(key);
}

ctx.log.Done();
}
