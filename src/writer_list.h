#pragma once
#include "PickleContext.h"
#include <vector>

using WriteFunc = void(*)(PickleContext&);
std::vector<WriteFunc> GetWriters(const PickleContext& ctx);
