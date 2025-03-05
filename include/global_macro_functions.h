#pragma once

//////////////////////////////////////////////////////////////////////////////////////////////

// FunctionRunner is used to register functions to be run at the start of the program.

#include <functional>

namespace _GlobalMacroFunctions {
    struct FunctionRunner {
        FunctionRunner(std::function<void()> func) { func(); }
    };
}

//////////////////////////////////////////////////////////////////////////////////////////////

// Generic Helper Macros

#define _GLOBAL_MACRO_FUNCTIONS_EXPAND(symbol) symbol

#define _GLOBAL_MACRO_FUNCTIONS_STRINGIZE_CORE(symbol) #symbol

#define _GLOBAL_MACRO_FUNCTIONS_STRINGIZE(symbol) _GLOBAL_MACRO_FUNCTIONS_STRINGIZE_CORE(symbol)

#define _GLOBAL_MACRO_FUNCTIONS_CONCAT_CORE(a, b) a##b

#define _GLOBAL_MACRO_FUNCTIONS_CONCAT(a, b) _GLOBAL_MACRO_FUNCTIONS_CONCAT_CORE(a, b)

//////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _GLOBAL_MACRO_FUNCTIONS_COMPILATION_UNIT_NAME
    #define _GLOBAL_MACRO_FUNCTIONS_COMPILATION_UNIT_NAME _DefaultCompilationUnit_
#endif

// Provide your own macro to provide unique constants
// or fall back to the default implementation which concatenates the symbol with the compilation
// unit name

#ifndef GLOBAL_MACRO_COMPILATION_UNIT_CONSTANT
    #define GLOBAL_MACRO_COMPILATION_UNIT_CONSTANT(symbol) \
        _GLOBAL_MACRO_FUNCTIONS_CONCAT(symbol, _GLOBAL_MACRO_FUNCTIONS_COMPILATION_UNIT_NAME)
#endif

//////////////////////////////////////////////////////////////////////////////////////////////

#define _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_RUNNER_VARIABLE_NAME_FROM_COUNT(symbol, count) \
    _GlobalMacroFunctions::FunctionRunner _GLOBAL_MACRO_FUNCTIONS_CONCAT(                         \
        GLOBAL_MACRO_COMPILATION_UNIT_CONSTANT(                                                   \
            _GLOBAL_MACRO_FUNCTIONS_CONCAT(__globalMacroFunctions__functionRunner__, symbol)      \
        ),                                                                                        \
        count                                                                                     \
    )

#define _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_RUNNER_VARIABLE_NAME(symbol) \
    _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_RUNNER_VARIABLE_NAME_FROM_COUNT(symbol, __COUNTER__)

//////////////////////////////////////////////////////////////////////////////////////////////

#define _GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_RUNNER_VARIABLE_NAME_FROM_COUNT(count)             \
    _GlobalMacroFunctions::FunctionRunner _GLOBAL_MACRO_FUNCTIONS_CONCAT(                       \
        GLOBAL_MACRO_COMPILATION_UNIT_CONSTANT(__globalMacroFunctions__functionRunner__), count \
    )

#define _GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_RUNNER_VARIABLE_NAME \
    _GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_RUNNER_VARIABLE_NAME_FROM_COUNT(__COUNTER__)

//////////////////////////////////////////////////////////////////////////////////////////////

#define _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)      \
    _GLOBAL_MACRO_FUNCTIONS_CONCAT(                                                    \
        GLOBAL_MACRO_COMPILATION_UNIT_CONSTANT(                                        \
            _GLOBAL_MACRO_FUNCTIONS_CONCAT(__globalMacroFunctions__function__, symbol) \
        ),                                                                             \
        count                                                                          \
    )

#define _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME(symbol) \
    _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, __COUNTER__)

//////////////////////////////////////////////////////////////////////////////////////////////

#define _GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_NAME_FROM_COUNT(count)                       \
    _GLOBAL_MACRO_FUNCTIONS_CONCAT(                                                       \
        GLOBAL_MACRO_COMPILATION_UNIT_CONSTANT(__globalMacroFunctions__function__), count \
    )

#define _GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_NAME() \
    _GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_NAME_FROM_COUNT(__COUNTER__)

//////////////////////////////////////////////////////////////////////////////////////////////

#define __GLOBAL_MACRO_FUNCTIONS_RUN_BODY(count)                                    \
    inline void _GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_NAME_FROM_COUNT(count)();      \
    namespace {                                                                     \
        _GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_RUNNER_VARIABLE_NAME_FROM_COUNT(count  \
        ){[]() { _GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_NAME_FROM_COUNT(count)(); }}; \
    }                                                                               \
    inline void _GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_NAME_FROM_COUNT(count)

#define _GLOBAL_MACRO_FUNCTIONS_RUN() __GLOBAL_MACRO_FUNCTIONS_RUN_BODY(__COUNTER__)()

//////////////////////////////////////////////////////////////////////////////////////////////

#define __GLOBAL_MACRO_FUNCTIONS_RUN_NAMED_BODY(symbol, count)                                     \
    inline void _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)();       \
    namespace {                                                                                    \
        _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_RUNNER_VARIABLE_NAME_FROM_COUNT(symbol, count){ \
            []() {                                                                                 \
                _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)          \
                ();                                                                                \
            }                                                                                      \
        };                                                                                         \
    }                                                                                              \
    inline void _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)

#define _GLOBAL_MACRO_FUNCTIONS_RUN_NAMED(symbol) \
    __GLOBAL_MACRO_FUNCTIONS_RUN_NAMED_BODY(symbol, __COUNTER__)()

//////////////////////////////////////////////////////////////////////////////////////////////

#define __GLOBAL_MACRO_FUNCTIONS_REGISTER_NEW_FUNCTION_BODY(registrationFunction, count)        \
    inline void _GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_NAME_FROM_COUNT(count)();                  \
    namespace {                                                                                 \
        _GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_RUNNER_VARIABLE_NAME_FROM_COUNT(count){[]() {      \
            registrationFunction(&_GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_NAME_FROM_COUNT(count)); \
        }};                                                                                     \
    }                                                                                           \
    inline void _GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_NAME_FROM_COUNT(count)

#define _GLOBAL_MACRO_FUNCTIONS_REGISTER_NEW_FUNCTION(registrationFunction) \
    __GLOBAL_MACRO_FUNCTIONS_REGISTER_NEW_FUNCTION_BODY(registrationFunction, __COUNTER__)

//////////////////////////////////////////////////////////////////////////////////////////////

#define __GLOBAL_MACRO_FUNCTIONS_REGISTER_NEW_NAMED_FUNCTION_BODY(                                 \
    symbol, registrationFunction, count                                                            \
)                                                                                                  \
    inline void _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)();       \
    namespace {                                                                                    \
        _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_RUNNER_VARIABLE_NAME_FROM_COUNT(symbol, count){ \
            []() {                                                                                 \
                registrationFunction(                                                              \
                    &_GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)     \
                );                                                                                 \
            }                                                                                      \
        };                                                                                         \
    }                                                                                              \
    inline void _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)

#define _GLOBAL_MACRO_FUNCTIONS_REGISTER_NEW_NAMED_FUNCTION(symbol, registrationFunction) \
    __GLOBAL_MACRO_FUNCTIONS_REGISTER_NEW_NAMED_FUNCTION_BODY(                            \
        symbol, registrationFunction, __COUNTER__                                         \
    )

//////////////////////////////////////////////////////////////////////////////////////////////

#define __GLOBAL_MACRO_FUNCTIONS_REGISTER_NEW_NAMED_FUNCTION_WITH_RETURN_BODY(                     \
    symbol, registrationFunction, returnType, count                                                \
)                                                                                                  \
    inline returnType _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)(); \
    namespace {                                                                                    \
        _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_RUNNER_VARIABLE_NAME_FROM_COUNT(symbol, count){ \
            []() {                                                                                 \
                registrationFunction(                                                              \
                    &_GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)     \
                );                                                                                 \
            }                                                                                      \
        };                                                                                         \
    }                                                                                              \
    inline returnType _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)

#define _GLOBAL_MACRO_FUNCTIONS_REGISTER_NEW_NAMED_FUNCTION_WITH_RETURN(   \
    symbol, registrationFunction                                           \
)                                                                          \
    __GLOBAL_MACRO_FUNCTIONS_REGISTER_NEW_NAMED_FUNCTION_WITH_RETURN_BODY( \
        symbol, registrationFunction, returnType, __COUNTER__              \
    )

//////////////////////////////////////////////////////////////////////////////////////////////

#define __GLOBAL_MACRO_FUNCTIONS_REGISTER_NEW_FUNCTION_WITH_ARGUMENTS_BODY(                     \
    registrationFunction, count, ...                                                            \
)                                                                                               \
    inline void _GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_NAME_FROM_COUNT(count)(__VA_ARGS__);       \
    namespace {                                                                                 \
        _GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_RUNNER_VARIABLE_NAME_FROM_COUNT(count){[]() {      \
            registrationFunction(&_GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_NAME_FROM_COUNT(count)); \
        }};                                                                                     \
    }                                                                                           \
    inline void _GLOBAL_MACRO_FUNCTIONS_NEW_FUNCTION_NAME_FROM_COUNT(count)

#define _GLOBAL_MACRO_FUNCTIONS_REGISTER_NEW_FUNCTION_WITH_ARGUMENTS(registrationFunction, ...) \
    __GLOBAL_MACRO_FUNCTIONS_REGISTER_NEW_FUNCTION_WITH_ARGUMENTS_BODY(                         \
        registrationFunction, __COUNTER__, __VA_ARGS__                                          \
    )

//////////////////////////////////////////////////////////////////////////////////////////////

#define __GLOBAL_MACRO_FUNCTIONS_REGISTER_NEW_NAMED_FUNCTION_WITH_ARGUMENTS_BODY(                  \
    symbol, registrationFunction, count, ...                                                       \
)                                                                                                  \
    inline void _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)(         \
        __VA_ARGS__                                                                                \
    );                                                                                             \
    namespace {                                                                                    \
        _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_RUNNER_VARIABLE_NAME_FROM_COUNT(symbol, count){ \
            []() {                                                                                 \
                registrationFunction(                                                              \
                    &_GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)     \
                );                                                                                 \
            }                                                                                      \
        };                                                                                         \
    }                                                                                              \
    inline void _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)

#define _GLOBAL_MACRO_FUNCTIONS_REGISTER_NEW_NAMED_FUNCTION_WITH_ARGUMENTS(   \
    symbol, registrationFunction, ...                                         \
)                                                                             \
    __GLOBAL_MACRO_FUNCTIONS_REGISTER_NEW_NAMED_FUNCTION_WITH_ARGUMENTS_BODY( \
        symbol, registrationFunction, __COUNTER__, __VA_ARGS__                \
    )

//////////////////////////////////////////////////////////////////////////////////////////////

#define __GLOBAL_MACRO_FUNCTIONS_REGISTER_NEW_NAMED_FUNCTION_WITH_RETURN_AND_ARGUMENTS_BODY(       \
    symbol, registrationFunction, returnType, count, ...                                           \
)                                                                                                  \
    inline returnType _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)(   \
        __VA_ARGS__                                                                                \
    );                                                                                             \
    namespace {                                                                                    \
        _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_RUNNER_VARIABLE_NAME_FROM_COUNT(symbol, count){ \
            []() {                                                                                 \
                registrationFunction(                                                              \
                    &_GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)     \
                );                                                                                 \
            }                                                                                      \
        };                                                                                         \
    }                                                                                              \
    inline returnType _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)

#define _GLOBAL_MACRO_FUNCTIONS_REGISTER_NEW_NAMED_FUNCTION_WITH_RETURN_AND_ARGUMENTS(   \
    symbol, registrationFunction, returnType, ...                                        \
)                                                                                        \
    __GLOBAL_MACRO_FUNCTIONS_REGISTER_NEW_NAMED_FUNCTION_WITH_RETURN_AND_ARGUMENTS_BODY( \
        symbol, registrationFunction, returnType, __COUNTER__, __VA_ARGS__               \
    )

//////////////////////////////////////////////////////////////////////////////////////////////
