#include "PickleContext.h"
#include "f4se/GameReferences.h"
#include "util.h"

void WriteWorkshops(PickleContext& ctx) {
Json::Value root;
int count = 0;

for (UInt32 i = 0; i < (*g_dataHandler)->arrTESForm[FormType::kFormType_REF].count; ++i) {
TESObjectREFR* ref = DYNAMIC_CAST((*g_dataHandler)->arrTESForm[FormType::kFormType_REF].entries[i], TESForm, TESObjectREFR);
if (!ref || !ref->baseForm) continue;

std::string edid = GetEditorID(ref->baseForm);
if (edid.find("Workshop") == std::string::npos) continue;

Json::Value entry;
entry["population"] = 12; // Placeholder
entry["beds"] = 14;
entry["happiness"] = 85;

root[ModKeyForFormID(ref->formID)] = entry;
count++;
}

ctx.SaveJson("Workshops.json", root);
ctx.Log("Workshops: " + std::to_string(count));
}
