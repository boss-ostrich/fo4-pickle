#include <nlohmann/json.hpp>
#include "export_manager.h"
#include "f4se/ConsoleAPI.h"
#include "flag_parser.h"
#include "PickleContext.h"
#include "UnpickleContext.h"
#include "write_dispatcher.h"
#include "unpickle_dispatcher.h"

void ExportManager::RegisterCommand() {
Console_Print("FalloutPickle v0.2.8 loaded. Use: pickle | unpickle [flags]");

RegisterConsoleCommand("pickle", []() {
auto flags = FlagParser::Parse();
PickleContext ctx;
ctx.Init(flags);
RunAllWriters(ctx);
ctx.verboseLog.Flush(ctx.Path("ExportVerbose.log").string());
});

RegisterConsoleCommand("unpickle", []() {
auto flags = FlagParser::Parse();
UnpickleContext ctx;
if (!ctx.Load(flags.pathOverride.value_or(""))) {
Console_Print("Unpickle failed: could not load export folder.");
return;
}
ctx.flags = flags;
RunAllUnpickleSteps(ctx);
ctx.log.Flush((ctx.folder / "UnpickleVerbose.log").string());
ctx.resolver.Dump((ctx.folder / "FormResolution.log").string());
});
}
