#pragma once

#include <functional>

namespace _GlobalMacroFunctions {
    struct FunctionRunner {
        FunctionRunner(std::function<void()> func) { func(); }
    };
}

#if defined(COMPILATION_UNIT_NAME)
    #define _GLOBAL_MACRO_FUNCTIONS_COMPILATION_UNIT_NAME COMPILATION_UNIT_NAME
#elif defined(COMPILATION_UNIT)
    #define _GLOBAL_MACRO_FUNCTIONS_COMPILATION_UNIT_NAME COMPILATION_UNIT
#else
    #define _GLOBAL_MACRO_FUNCTIONS_COMPILATION_UNIT_NAME defaultCompilationUnit
#endif

#define _GLOBAL_MACRO_FUNCTIONS_CONCAT_SIMPLE(a, b) a##b

#define _GLOBAL_MACRO_FUNCTIONS_CONCAT(a, b) _GLOBAL_MACRO_FUNCTIONS_CONCAT_SIMPLE(a, b)

#ifndef COMPILATION_UNIT_CONSTANT
    #define COMPILATION_UNIT_CONSTANT(name) \
        _GLOBAL_MACRO_FUNCTIONS_CONCAT(name, _GLOBAL_MACRO_FUNCTIONS_COMPILATION_UNIT_NAME)
#endif

//////////////////////////////////////////////////////////////////////////////////////////////

#define _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_RUNNER_VARIABLE_NAME_FROM_COUNT(symbol, count) \
    _GlobalMacroFunctions::FunctionRunner _GLOBAL_MACRO_FUNCTIONS_CONCAT(                         \
        COMPILATION_UNIT_CONSTANT(                                                                \
            _GLOBAL_MACRO_FUNCTIONS_CONCAT(__globalMacroFunctions__functionRunner__, symbol)      \
        ),                                                                                        \
        count                                                                                     \
    )

#define _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_RUNNER_VARIABLE_NAME(symbol) \
    _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_RUNNER_VARIABLE_NAME_FROM_COUNT(symbol, __COUNTER__)

//////////////////////////////////////////////////////////////////////////////////////////////

#define _GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_RUNNER_VARIABLE_NAME_FROM_COUNT(count) \
    _GlobalMacroFunctions::FunctionRunner _GLOBAL_MACRO_FUNCTIONS_CONCAT(           \
        COMPILATION_UNIT_CONSTANT(__globalMacroFunctions__functionRunner__), count  \
    )

#define _GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_RUNNER_VARIABLE_NAME \
    _GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_RUNNER_VARIABLE_NAME_FROM_COUNT(__COUNTER__)

//////////////////////////////////////////////////////////////////////////////////////////////

#define _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)      \
    _GLOBAL_MACRO_FUNCTIONS_CONCAT(                                                    \
        COMPILATION_UNIT_CONSTANT(                                                     \
            _GLOBAL_MACRO_FUNCTIONS_CONCAT(__globalMacroFunctions__function__, symbol) \
        ),                                                                             \
        count                                                                          \
    )

#define _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME(symbol) \
    _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, __COUNTER__)

//////////////////////////////////////////////////////////////////////////////////////////////

#define _GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_NAME_FROM_COUNT(count)          \
    _GLOBAL_MACRO_FUNCTIONS_CONCAT(                                          \
        COMPILATION_UNIT_CONSTANT(__globalMacroFunctions__function__), count \
    )

#define _GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_NAME(count) \
    _GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_NAME_FROM_COUNT(__COUNTER__)

//////////////////////////////////////////////////////////////////////////////////////////////

#define _GLOBAL_MACRO_FUNCTIONS_RUN_BODY(count)                                        \
    inline void _GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_NAME_FROM_COUNT(count)();         \
    _GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_RUNNER_VARIABLE_NAME_FROM_COUNT(count){[]() { \
        _GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_NAME_FROM_COUNT(count)();                 \
    }};                                                                                \
    inline void _GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_NAME_FROM_COUNT(count)

#define _GLOBAL_MACRO_FUNCTIONS_RUN() _GLOBAL_MACRO_FUNCTIONS_RUN_BODY(__COUNTER__)()

//////////////////////////////////////////////////////////////////////////////////////////////

#define _GLOBAL_MACRO_FUNCTIONS_RUN_NAMED_BODY(symbol, count)                                  \
    inline void _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)();   \
    _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_RUNNER_VARIABLE_NAME_FROM_COUNT(symbol, count){ \
        []() {                                                                                 \
            _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)          \
            ();                                                                                \
        }};                                                                                    \
    inline void _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)

#define _GLOBAL_MACRO_FUNCTIONS_RUN_NAMED(symbol) \
    _GLOBAL_MACRO_FUNCTIONS_RUN_NAMED_BODY(symbol, __COUNTER__)()

//////////////////////////////////////////////////////////////////////////////////////////////

#define _GLOBAL_MACRO_FUNCTIONS_REGISTER_NEW_FUNCTION_BODY(registrationFunction, count)    \
    inline void _GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_NAME_FROM_COUNT(count)();             \
    _GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_RUNNER_VARIABLE_NAME_FROM_COUNT(count){[]() {     \
        registrationFunction(_GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_NAME_FROM_COUNT(count)); \
    }};                                                                                    \
    inline void _GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_NAME_FROM_COUNT(count)

#define _GLOBAL_MACRO_FUNCTIONS_REGISTER_NEW_FUNCTION(registrationFunction) \
    _GLOBAL_MACRO_FUNCTIONS_REGISTER_NEW_FUNCTION_BODY(registrationFunction, __COUNTER__)

//////////////////////////////////////////////////////////////////////////////////////////////

#define _GLOBAL_MACRO_FUNCTIONS_REGISTER_NEW_NAMED_FUNCTION_BODY(                              \
    symbol, registrationFunction, count                                                        \
)                                                                                              \
    inline void _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)();   \
    _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_RUNNER_VARIABLE_NAME_FROM_COUNT(symbol, count){ \
        []() {                                                                                 \
            registrationFunction(                                                              \
                _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)      \
            );                                                                                 \
        }};                                                                                    \
    inline void _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)

#define _GLOBAL_MACRO_FUNCTIONS_REGISTER_NEW_NAMED_FUNCTION(symbol, registrationFunction) \
    _GLOBAL_MACRO_FUNCTIONS_REGISTER_NEW_NAMED_FUNCTION_BODY(                             \
        symbol, registrationFunction, __COUNTER__                                         \
    )

//////////////////////////////////////////////////////////////////////////////////////////////

#define _GLOBAL_MACRO_FUNCTIONS_REGISTER_NEW_FUNCTION_WITH_ARGUMENTS_BODY(                 \
    registrationFunction, count, ...                                                       \
)                                                                                          \
    inline void _GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_NAME_FROM_COUNT(count)(__VA_ARGS__);  \
    _GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_RUNNER_VARIABLE_NAME_FROM_COUNT(count){[]() {     \
        registrationFunction(_GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_NAME_FROM_COUNT(count)); \
    }};                                                                                    \
    inline void _GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_NAME_FROM_COUNT(count)

#define _GLOBAL_MACRO_FUNCTIONS_REGISTER_NEW_FUNCTION_WITH_ARGUMENTS(registrationFunction, ...) \
    _GLOBAL_MACRO_FUNCTIONS_REGISTER_NEW_FUNCTION_WITH_ARGUMENTS_BODY(                          \
        registrationFunction, __COUNTER__, __VA_ARGS__                                          \
    )

//////////////////////////////////////////////////////////////////////////////////////////////

#define _GLOBAL_MACRO_FUNCTIONS_REGISTER_NEW_NAMED_FUNCTION_WITH_ARGUMENTS_BODY(               \
    symbol, registrationFunction, count, ...                                                   \
)                                                                                              \
    inline void _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)(     \
        __VA_ARGS__                                                                            \
    );                                                                                         \
    _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_RUNNER_VARIABLE_NAME_FROM_COUNT(symbol, count){ \
        []() {                                                                                 \
            registrationFunction(                                                              \
                _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)      \
            );                                                                                 \
        }};                                                                                    \
    inline void _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)

#define _GLOBAL_MACRO_FUNCTIONS_REGISTER_NEW_NAMED_FUNCTION_WITH_ARGUMENTS(  \
    symbol, registrationFunction, ...                                        \
)                                                                            \
    _GLOBAL_MACRO_FUNCTIONS_REGISTER_NEW_NAMED_FUNCTION_WITH_ARGUMENTS_BODY( \
        symbol, registrationFunction, __COUNTER__, __VA_ARGS__               \
    )

//////////////////////////////////////////////////////////////////////////////////////////////
