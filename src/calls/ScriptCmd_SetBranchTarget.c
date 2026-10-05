#include "nitro/types.h"

int ScriptCmd_SetBranchTarget(int scriptCtx, int *cmd)
{
    int operand = *cmd;
    int count = *(int *)(scriptCtx + 0x1c4);
    int entry = scriptCtx + 4 + count * 0x70;

    if (operand != -1) {
        *(int *)(scriptCtx + 0x620) = count;
        *(int *)(scriptCtx + 0x624) = *(int *)(entry + 0xc) + operand;
    } else {
        *(int *)(scriptCtx + 0x624) = 0;
    }
    *(int *)(scriptCtx + 0x628) = 0;
    return 1;
}
