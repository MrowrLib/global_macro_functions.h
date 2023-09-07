#include <_Log_.h>
#include <global_macro_functions.h>

#include <functional>
#include <vector>

using namespace std;

class StoresCoolBlocksOfCode {
    vector<function<void()>>         _codeBlocks;
    vector<function<void(int, int)>> _codeBlocksWithArguments;

public:
    void AddCodeBlock(function<void()> codeBlock) { _codeBlocks.push_back(codeBlock); }
    void AddCodeBlockWithArguments(function<void(int, int)> codeBlock) {
        _codeBlocksWithArguments.push_back(codeBlock);
    }

    void ExecuteAllCodeBlocks(int arg1 = 69, int arg2 = 420) {
        for (auto codeBlock : _codeBlocks) codeBlock();
        for (auto codeBlock : _codeBlocksWithArguments) codeBlock(arg1, arg2);
    }
};

StoresCoolBlocksOfCode TheMainBlocksOfCode;

#define CoolBlockOfCode                                                             \
    _GLOBAL_MACRO_FUNCTIONS_REGISTER_NEW_FUNCTION(TheMainBlocksOfCode.AddCodeBlock) \
    ()

// Global code blocks (with arguments)
CoolBlockOfCode { _Log_("Hello from FIRST CoolBlockOfCode!"); }
CoolBlockOfCode { _Log_("Hello from SECOND CoolBlockOfCode!"); }

#define BlockWithArguments                                        \
    _GLOBAL_MACRO_FUNCTIONS_REGISTER_NEW_FUNCTION_WITH_ARGUMENTS( \
        TheMainBlocksOfCode.AddCodeBlockWithArguments, int, int   \
    )

// Global code blocks (with arguments)
BlockWithArguments(int arg1, int arg2) {
    _Log_("Hello from BlockWithArguments! arg1 = {}, arg2 = {}", arg1, arg2);
}

// TODO
// // Pass along other arguments to the block registration function

// RegisterNamedBlock("Name One") {
//     _Log_("Hello from NamedBlock! Name = {}", name);
// }

// RegisterNamedBlock("Name Two") {
//     _Log_("Hello from NamedBlock! Name = {}", name);
// }

// And an arbitrary lambda that runs at the start of main
#define RunMe _GLOBAL_MACRO_FUNCTIONS_RUN()

RunMe { _Log_("Hello from RunMe!"); }

int main() {
    _Log_("Hello from main!");
    TheMainBlocksOfCode.ExecuteAllCodeBlocks();
    return 0;
}
