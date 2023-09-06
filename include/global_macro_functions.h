#pragma once

#include <functional>

namespace _GlobalMacroFunctions {
    struct FunctionRunner {
        FunctionRunner(std::function<void()> func) { func(); }
    };
}

#define _GLOBAL_MACRO_FUNCTIONS_CONCAT_SIMPLE(a, b) a##b

#define _GLOBAL_MACRO_FUNCTIONS_CONCAT(a, b) _GLOBAL_MACRO_FUNCTIONS_CONCAT_SIMPLE(a, b)

#define _GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_RUNNER_VARIABLE_NAME_FROM_COUNT(count) \
    _GlobalMacroFunctions::FunctionRunner _GLOBAL_MACRO_FUNCTIONS_CONCAT(           \
        __dslMaker__functionRunner__, count                                         \
    )

#define _GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_RUNNER_VARIABLE_NAME \
    _GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_RUNNER_VARIABLE_NAME_FROM_COUNT(__COUNTER__)

#define _GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_NAME_FROM_COUNT(count) \
    _GLOBAL_MACRO_FUNCTIONS_CONCAT(__dslMaker__function__, count)

#define _GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_NAME(count) \
    _GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_NAME_FROM_COUNT(__COUNTER__)

#define _GLOBAL_MACRO_FUNCTIONS_REGISTER_NEW_FUNCTION_BODY(lambdaRegistrationFunction, count)    \
    inline void _GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_NAME_FROM_COUNT(count)();                   \
    _GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_RUNNER_VARIABLE_NAME_FROM_COUNT(count){[]() {           \
        lambdaRegistrationFunction(_GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_NAME_FROM_COUNT(count)); \
    }};                                                                                          \
    inline void _GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_NAME_FROM_COUNT(count)

#define _GLOBAL_MACRO_FUNCTIONS_REGISTER_NEW_FUNCTION(lambdaRegistrationFunction) \
    _GLOBAL_MACRO_FUNCTIONS_REGISTER_NEW_FUNCTION_BODY(lambdaRegistrationFunction, __COUNTER__)

#define _GLOBAL_MACRO_FUNCTIONS_REGISTER_NEW_FUNCTION_WITH_ARGUMENTS_BODY(                       \
    lambdaRegistrationFunction, count, ...                                                       \
)                                                                                                \
    inline void _GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_NAME_FROM_COUNT(count)(__VA_ARGS__);        \
    _GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_RUNNER_VARIABLE_NAME_FROM_COUNT(count){[]() {           \
        lambdaRegistrationFunction(_GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_NAME_FROM_COUNT(count)); \
    }};                                                                                          \
    inline void _GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_NAME_FROM_COUNT(count)

#define _GLOBAL_MACRO_FUNCTIONS_REGISTER_NEW_FUNCTION_WITH_ARGUMENTS(  \
    lambdaRegistrationFunction, ...                                    \
)                                                                      \
    _GLOBAL_MACRO_FUNCTIONS_REGISTER_NEW_FUNCTION_WITH_ARGUMENTS_BODY( \
        lambdaRegistrationFunction, __COUNTER__, __VA_ARGS__           \
    )
