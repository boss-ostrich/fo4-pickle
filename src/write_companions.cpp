#include "PickleContext.h"
#include "f4se/GameReferences.h"
#include "f4se/GameRTTI.h"
#include "util.h"

void WriteCompanions(PickleContext& ctx) {
Json::Value root;
PlayerCharacter* player = *g_thePlayer;
if (!player) return;

for (UInt32 i = 0; i < (*g_dataHandler)->arrTESForm[FormType::kFormType_NPC].count; ++i) {
TESNPC* npc = DYNAMIC_CAST((*g_dataHandler)->arrTESForm[FormType::kFormType_NPC].entries[i], TESForm, TESNPC);
if (!npc || !npc->editorId) continue;

std::string idStr = npc->editorId;
if (idStr.find("Companion") == std::string::npos) continue;

Json::Value entry;
entry["name"] = npc->fullName.GetName();
entry["appearance_preset"] = "Presets/" + idStr + ".json";

TESObjectREFR* ref = DYNAMIC_CAST(npc, TESForm, TESObjectREFR);
if (!ref) continue;

Json::Value gear, inv, eq;

ExtraContainerChanges* changes = static_cast<ExtraContainerChanges*>(ref->extraData.GetByType(kExtraData_ContainerChanges));
if (changes && changes->data && changes->data->objList) {
for (auto obj : *changes->data->objList) {
if (!obj || !obj->form) continue;
inv[ModKeyForFormID(obj->form->formID)] = obj->countDelta;
}
}

BaseExtraList* extraList = &ref->extraData;
if (extraList->HasType(kExtraData_Worn)) {
for (UInt32 i = 0; i < changes->data->objList->count; i++) {
auto item = changes->data->objList->entries[i];
if (item && item->form)
eq[ModKeyForFormID(item->form->formID)] = 1;
}
}

gear["inventory"] = inv;
gear["equipped"] = eq;
entry["gear"] = gear;
root[ModKeyForFormID(npc->formID)] = entry;

ctx.verboseLog.Info("Exported companion gear for: " + idStr);
}

ctx.SaveJson("Companions.json", root);
ctx.Log("Companions: " + std::to_string(root.size()));
}
