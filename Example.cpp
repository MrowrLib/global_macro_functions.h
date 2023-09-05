#include <_Log_.h>
#include <dsl_maker.h>

#include <functional>
#include <vector>

using namespace std;

class StoresCoolBlocksOfCode {
    vector<function<void()>> _codeBlocks;

public:
    void AddCodeBlock(function<void()> codeBlock) { _codeBlocks.push_back(codeBlock); }

    void ExecuteAllCodeBlocks() {
        for (auto codeBlock : _codeBlocks) codeBlock();
    }
};

StoresCoolBlocksOfCode TheMainBlocksOfCode;

#define CoolBlockOfCode \
    _DSL_MAKER_REGISTER_NEW_FUNCTION_LAMBDA(TheMainBlocksOfCode.AddCodeBlock, __COUNTER__)()

// DSL blocks (with no arguments)
CoolBlockOfCode { _Log_("Hello from FIRST CoolBlockOfCode!"); }
CoolBlockOfCode { _Log_("Hello from SECOND CoolBlockOfCode!"); }

int main() {
    _Log_("Hello from main!");
    TheMainBlocksOfCode.ExecuteAllCodeBlocks();
    return 0;
}