#include "unpickle_context.h"
#include "util.h"

void RestoreWorkshops(const Json::Value& data, UnpickleContext& ctx) {
ctx.log.StartPhase("Restoring Workshops");

for (const auto& key : data.getMemberNames()) {
UInt32 fid = ResolveFormID(key);
TESObjectREFR* ref = DYNAMIC_CAST(LookupFormByID(fid), TESForm, TESObjectREFR);
if (!ref) {
ctx.resolver.RecordFailure(key);
ctx.log.Warn("Workshop not found: " + key);
continue;
}

ctx.resolver.RecordSuccess(key);
ctx.log.Info("Workshop: " + key);

for (const auto& kv : data[key].getMemberNames()) {
auto value = data[key][kv].asInt();
if (ctx.IsDryRun()) {
ctx.log.Info("[dryrun] Would set " + kv + " = " + std::to_string(value));
} else {
ctx.log.Info("Stubbed: set " + kv + " = " + std::to_string(value));
}
}
}

ctx.log.Done();
}
