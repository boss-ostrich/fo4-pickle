#include <nlohmann/json.hpp>
#include "PickleContext.h"
#include "f4se/GameReferences.h"
#include "f4se/GameObjects.h"
#include "util.h"

void WriteInventory(PickleContext& ctx) {
Json::Value inv;
PlayerCharacter* player = *g_thePlayer;
if (!player) return;

ExtraContainerChanges* changes = static_cast<ExtraContainerChanges*>(player->extraData.GetByType(kExtraData_ContainerChanges));
if (!changes || !changes->data || !changes->data->objList) return;

for (auto entry : *changes->data->objList) {
if (!entry || !entry->form) continue;
inv[ModKeyForFormID(entry->form->formID)] = entry->countDelta;
}

ctx.SaveJson("Inventory.json", inv);
ctx.Log("Inventory exported");
ctx.verboseLog.Info("Exported " + std::to_string(inv.size()) + " inventory items");
}
