#include "nitro/types.h"

extern short *ScriptVm_ResolveOperand(int scriptCtx, unsigned short *operand);
extern int func_0202b79c(void);

int ByteCode_ResolveOperand(int scriptCtx, unsigned short *operand)
{
    int base = scriptCtx + 4 + *(int *)(scriptCtx + 0x1c4) * 0x70;
    short *resolved = ScriptVm_ResolveOperand(scriptCtx, operand);

    if (*resolved == 0x40) {
        int indexBase = *(int *)(base + 0x14) + *(volatile int *)(resolved + 2);
        int selector = func_0202b79c();
        return *(int *)(base + 0x14) + *(int *)(indexBase + selector * 4);
    }
    return *(int *)(base + 0x14) + *(volatile int *)(resolved + 2);
}

