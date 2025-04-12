#include "PickleContext.h"
#include "f4se/GameReferences.h"
#include "f4se/GameForms.h"
#include "f4se/GameRTTI.h"
#include "util.h"

void WriteMap(PickleContext& ctx) {
Json::Value root;
PlayerCharacter* player = *g_thePlayer;
if (!player) return;

root["current_location"] = FormIDToHex(player->parentCell ? player->parentCell->formID : 0);
Json::Value markers(Json::arrayValue);

for (UInt32 i = 0; i < (*g_dataHandler)->arrTESForm[FormType::kFormType_ACHR].count; ++i) {
TESObjectREFR* ref = DYNAMIC_CAST((*g_dataHandler)->arrTESForm[FormType::kFormType_ACHR].entries[i], TESForm, TESObjectREFR);
if (!ref) continue;

ExtraMapMarker* marker = static_cast<ExtraMapMarker*>(ref->extraData.GetByType(kExtraData_MapMarker));
if (marker && marker->mapData && (marker->mapData->flags.flags & 0x01)) {
Json::Value m;
m["id"] = ModKeyForFormID(ref->formID);
m["name"] = ref->baseForm && ref->baseForm->GetFullName() ? ref->baseForm->GetFullName() : "";
markers.append(m);
}
}

root["discovered_markers"] = markers;
ctx.SaveJson("Map.json", root);
ctx.Log("Map markers: " + std::to_string(markers.size()));
}
