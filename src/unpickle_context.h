#pragma once

#include "PickleContext.h"
#include <string>

class UnpickleContext {
public:
    explicit UnpickleContext(PickleContext& pickle) : pickle(pickle) {}

    PickleContext& pickle;

    // Add more helper methods as needed
};
