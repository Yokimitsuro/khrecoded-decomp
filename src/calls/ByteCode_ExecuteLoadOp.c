#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x1c4];
    s32 currentIndex;
} ScriptVm;

extern int IsRecordIdFree(void *addr);
extern void func_0202d328(void *addr, int flag);
extern int ByteCode_ResolveOperand(int scriptCtx, unsigned short *operand);
extern int ScriptVm_PushFrame(ScriptVm *vm, void *addr, int value, int result);

int ByteCode_ExecuteLoadOp(ScriptVm *vm, u8 *param2)
{
    int bufferBase = *(int *)vm;
    int bufferPos = *(int *)((u8 *)vm + 0x63c);
    int value;
    int result;

    if (IsRecordIdFree((void *)(bufferPos + bufferBase)) == 0) {
        return 0;
    }
    if (*(int *)(bufferPos + bufferBase) == 0x504b4143) {
        func_0202d328((void *)(bufferPos + bufferBase), 0);
    }
    value = *(int *)((u8 *)vm + (vm->currentIndex + 1) * 0x70 + 8);
    if (*(short *)(param2 + 8) != 0) {
        result = ByteCode_ResolveOperand((int)vm, (unsigned short *)(param2 + 8));
    } else {
        result = 0;
    }
    ScriptVm_PushFrame(vm, (void *)(bufferPos + bufferBase), value, result);
    return 2;
}
