#include <nlohmann/json.hpp>
#include "PickleContext.h"
#include "f4se/GameReferences.h"
#include "f4se/GameData.h"
#include "f4se/GameForms.h"
#include "util.h"

void WriteCharacter(PickleContext& ctx) {
PlayerCharacter* player = *g_thePlayer;
if (!player) return;

Json::Value root;
root["name"] = ctx.characterName;
root["level"] = player->GetLevel();

float xp = player->actorValueOwner.GetCurrent(ActorValueList::GetSingleton()->GetActorValue(0x21));
root["xp"] = static_cast<int>(xp);
ctx.verboseLog.Info("XP: " + std::to_string((int)xp));

Json::Value special;
UInt32 baseFormIDs[] = { 0x2D4, 0x2D5, 0x2D6, 0x2D7, 0x2D8, 0x2D9, 0x2DA };
for (int i = 0; i < 7; ++i) {
auto av = ActorValueList::GetSingleton()->GetActorValue(i);
special[ModKeyForFormID(baseFormIDs[i])] = player->actorValueOwner.GetCurrent(av);
}
root["special_values"] = special;

ctx.SaveJson("Character.json", root);
ctx.Log("Character exported");
ctx.verboseLog.Info("Character export complete");
}
