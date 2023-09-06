#include <_Log_.h>
#include <dsl_maker.h>

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

#define CoolBlockOfCode \
    _DSL_MAKER_REGISTER_NEW_FUNCTION_LAMBDA(TheMainBlocksOfCode.AddCodeBlock, __COUNTER__)()

// DSL blocks (with no arguments)
CoolBlockOfCode { _Log_("Hello from FIRST CoolBlockOfCode!"); }
CoolBlockOfCode { _Log_("Hello from SECOND CoolBlockOfCode!"); }

#define BlockWithArguments                                                   \
    _DSL_MAKER_REGISTER_NEW_FUNCTION_WITH_ARGUMENTS(                         \
        TheMainBlocksOfCode.AddCodeBlockWithArguments, __COUNTER__, int, int \
    )

BlockWithArguments(int arg1, int arg2) {
    _Log_("Hello from BlockWithArguments! arg1 = {}, arg2 = {}", arg1, arg2);
}

// NEXT: ones which have the (...) argument block please :)

int main() {
    _Log_("Hello from main!");
    TheMainBlocksOfCode.ExecuteAllCodeBlocks();
    return 0;
}