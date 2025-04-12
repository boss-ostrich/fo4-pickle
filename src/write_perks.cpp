#include "PickleContext.h"
#include "f4se/GameReferences.h"
#include "f4se/GameRTTI.h"
#include "util.h"

void WritePerks(PickleContext& ctx) {
PlayerCharacter* player = *g_thePlayer;
if (!player || !player->perkRanks) return;

Json::Value perks;
UInt32 count = 0;

for (UInt32 i = 0; i < player->perkRanks->Count(); i++) {
BGSPerk* perk = nullptr;
UInt8 rank = 0;
player->perkRanks->GetNthItem(i, perk);
player->perkRanks->GetNthItemExtra(i, rank);
if (perk) {
perks[ModKeyForFormID(perk->formID)] = rank;
count++;
}
}

ctx.SaveJson("Perks.json", perks);
ctx.Log("Perks: " + std::to_string(count));
ctx.verboseLog.Info("Exported " + std::to_string(count) + " perks");
}
