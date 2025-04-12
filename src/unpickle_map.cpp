#include "unpickle_context.h"
#include "f4se/GameReferences.h"
#include "f4se/GameForms.h"
#include "f4se/GameRTTI.h"
#include "util.h"

void RestoreMapMarkers(const Json::Value& map, UnpickleContext& ctx) {
ctx.log.StartPhase("Restoring Map Markers");

if (!map.isMember("discovered_markers")) {
ctx.log.Warn("No discovered_markers section.");
ctx.log.Done();
return;
}

for (const auto& m : map["discovered_markers"]) {
std::string key = m["id"].asString();
UInt32 fid = ResolveFormID(key);
TESObjectREFR* ref = DYNAMIC_CAST(LookupFormByID(fid), TESForm, TESObjectREFR);

if (!ref) {
ctx.resolver.RecordFailure(key);
ctx.log.Warn("Map marker not found: " + key);
continue;
}

ctx.resolver.RecordSuccess(key);
if (ctx.IsDryRun()) {
ctx.log.Info("[dryrun] Would mark " + key + " as discovered");
} else {
ExtraMapMarker* marker = static_cast<ExtraMapMarker*>(ref->extraData.GetByType(kExtraData_MapMarker));
if (marker && marker->mapData)
marker->mapData->flags.flags |= 0x01;
ctx.log.Info("Marked " + key + " as discovered");
}
}

ctx.log.Done();
}
