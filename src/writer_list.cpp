#include "writer_list.h"
#include "write_character.cpp"
#include "write_perks.cpp"
#include "write_globals.cpp"
#include "write_inventory.cpp"
#include "write_companions.cpp"
#include "write_map.cpp"
#include "write_quests.cpp"
#include "write_workshops.cpp"

std::vector<WriteFunc> GetWriters(const PickleContext& ctx) {
std::vector<WriteFunc> writers;

if (ctx.flags.IsEnabled("character"))   writers.push_back(WriteCharacter);
if (ctx.flags.IsEnabled("perks"))       writers.push_back(WritePerks);
if (ctx.flags.IsEnabled("globals"))     writers.push_back(WriteGlobals);
if (ctx.flags.IsEnabled("inventory"))   writers.push_back(WriteInventory);
if (ctx.flags.IsEnabled("companions"))  writers.push_back(WriteCompanions);
if (ctx.flags.IsEnabled("map"))         writers.push_back(WriteMap);
if (ctx.flags.IsEnabled("quests"))      writers.push_back(WriteQuests);
if (ctx.flags.IsEnabled("workshops"))   writers.push_back(WriteWorkshops);

return writers;
}
