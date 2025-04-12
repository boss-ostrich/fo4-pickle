#include "write_dispatcher.h"
#include "writer_list.h"

void RunAllWriters(PickleContext& ctx) {
for (auto fn : GetWriters(ctx)) {
fn(ctx);
}
}
