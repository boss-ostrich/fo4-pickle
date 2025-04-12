#include "unpickle_context.h"
#include "util.h"

#include "unpickle_character.cpp"
#include "unpickle_perks.cpp"
#include "unpickle_globals.cpp"
#include "unpickle_quests.cpp"
#include "unpickle_companions.cpp"
#include "unpickle_map.cpp"
#include "unpickle_workshops.cpp"

void RunAllUnpickleSteps(UnpickleContext& ctx) {
ctx.log.StartPhase("Unpickle Start");

if (ctx.flags.IsEnabled("globals") && ctx.Has("Globals"))
ApplyGlobals(ctx["Globals"], ctx);

if (ctx.flags.IsEnabled("quests") && ctx.Has("Quests"))
RestoreQuestStages(ctx["Quests"], ctx);

if (ctx.flags.IsEnabled("xp") && ctx.Has("Character"))
ApplyXP(ctx["Character"]["xp"], ctx);

if (ctx.flags.IsEnabled("special") && ctx.Has("Character"))
RestoreSPECIAL(ctx["Character"]["special_values"], ctx);

if (ctx.flags.IsEnabled("perks") && ctx.Has("Perks"))
RestorePerks(ctx["Perks"], ctx);

if (ctx.flags.IsEnabled("companions") && ctx.Has("Companions"))
RestoreCompanions(ctx["Companions"], ctx);

if (ctx.flags.IsEnabled("map") && ctx.Has("Map"))
RestoreMapMarkers(ctx["Map"], ctx);

if (ctx.flags.IsEnabled("workshops") && ctx.Has("Workshops")) {
if (IsWorkshopFrameworkInstalled()) {
RestoreWorkshops(ctx["Workshops"], ctx);
} else {
ctx.log.Warn("WorkshopFramework not detected — skipping workshop restore.");
}
}

ctx.log.Done();
}
