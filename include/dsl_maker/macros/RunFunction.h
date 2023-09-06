#pragma once

#include "../FunctionRunner.h"  // IWYU pragma: keep
#include "Concat.h"

#define _DSL_MAKER_NEW_FUNCTION_RUNNER_VARIABLE_NAME_FROM_COUNT(count) \
    DSLMaker::FunctionRunner _DSL_MAKER_CONCAT(__dslMaker__functionRunner__, count)

#define _DSL_MAKER_NEW_FUNCTION_RUNNER_VARIABLE_NAME \
    _DSL_MAKER_NEW_FUNCTION_RUNNER_VARIABLE_NAME_FROM_COUNT(__COUNTER__)

#define _DSL_MAKER_NEW_FUNCTION_NAME_FROM_COUNT(count) \
    _DSL_MAKER_CONCAT(__dslMaker__function__, count)

#define _DSL_MAKER_NEW_FUNCTION_NAME(count) _DSL_MAKER_NEW_FUNCTION_NAME_FROM_COUNT(__COUNTER__)

#define _DSL_MAKER_REGISTER_NEW_FUNCTION(lambdaRegistrationFunction, count)                  \
    inline void _DSL_MAKER_NEW_FUNCTION_NAME_FROM_COUNT(count)();                            \
    _DSL_MAKER_NEW_FUNCTION_RUNNER_VARIABLE_NAME_FROM_COUNT(count                            \
    ){[]() { lambdaRegistrationFunction(_DSL_MAKER_NEW_FUNCTION_NAME_FROM_COUNT(count)); }}; \
    inline void _DSL_MAKER_NEW_FUNCTION_NAME_FROM_COUNT(count)

#define _DSL_MAKER_REGISTER_NEW_FUNCTION_WITH_ARGUMENTS(lambdaRegistrationFunction, count, ...) \
    inline void _DSL_MAKER_NEW_FUNCTION_NAME_FROM_COUNT(count)(__VA_ARGS__);                    \
    _DSL_MAKER_NEW_FUNCTION_RUNNER_VARIABLE_NAME_FROM_COUNT(count                               \
    ){[]() { lambdaRegistrationFunction(_DSL_MAKER_NEW_FUNCTION_NAME_FROM_COUNT(count)); }};    \
    inline void _DSL_MAKER_NEW_FUNCTION_NAME_FROM_COUNT(count)

#define _DSL_MAKER_REGISTER_NEW_FUNCTION_LAMBDA(lambdaRegistrationFunction, count)              \
    inline void _DSL_MAKER_NEW_FUNCTION_NAME_FROM_COUNT(count)();                               \
    _DSL_MAKER_NEW_FUNCTION_RUNNER_VARIABLE_NAME_FROM_COUNT(count){[]() {                       \
        lambdaRegistrationFunction([]() { _DSL_MAKER_NEW_FUNCTION_NAME_FROM_COUNT(count)(); }); \
    }};                                                                                         \
    inline void _DSL_MAKER_NEW_FUNCTION_NAME_FROM_COUNT(count)
