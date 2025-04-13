#include <nlohmann/json.hpp>
#include "unpickle_context.h"
#include "f4se/GameReferences.h"
#include "f4se/GameRTTI.h"
#include "util.h"

void RestoreCompanions(const Json::Value& companions, UnpickleContext& ctx) {
ctx.log.StartPhase("Restoring Companions");

for (const auto& key : companions.getMemberNames()) {
UInt32 formID = ResolveFormID(key);
TESNPC* npc = DYNAMIC_CAST(LookupFormByID(formID), TESForm, TESNPC);
if (!npc) {
ctx.log.Warn("Missing companion: " + key);
ctx.resolver.RecordFailure(key);
continue;
}

auto entry = companions[key];
std::string name = entry["name"].asString();

if (entry.isMember("name")) {
if (ctx.IsDryRun()) {
ctx.log.Info("[dryrun] Would rename to: " + name);
} else {
npc->fullName.Set(name.c_str());
}
}

if (entry.isMember("appearance_preset")) {
std::string path = entry["appearance_preset"].asString();
if (ctx.IsDryRun()) {
ctx.log.Info("[dryrun] Would apply Looksmenu preset: " + path);
} else {
ctx.log.Info("Would apply Looksmenu preset: " + path); // placeholder
}
}

if (entry.isMember("gear")) {
auto& gear = entry["gear"];
for (const auto& k : gear["inventory"].getMemberNames()) {
UInt32 fid = ResolveFormID(k);
TESForm* item = LookupFormByID(fid);
if (item) {
int count = gear["inventory"][k].asInt();
if (ctx.IsDryRun()) {
ctx.log.Info("[dryrun] Would add " + std::to_string(count) + " of " + k);
} else {
npc->AddItem(item, nullptr, count, false, false);
}
}
}
for (const auto& k : gear["equipped"].getMemberNames()) {
UInt32 fid = ResolveFormID(k);
TESForm* item = LookupFormByID(fid);
if (item) {
if (ctx.IsDryRun()) {
ctx.log.Info("[dryrun] Would equip " + k);
} else {
npc->EquipItem(item, 1, nullptr);
}
}
}
}

ctx.resolver.RecordSuccess(key);
}

ctx.log.Done();
}
