#pragma once

#include <functional>

namespace DSLMaker {
    struct FunctionRunner {
        FunctionRunner(std::function<void()> func) { func(); }
    };
}
