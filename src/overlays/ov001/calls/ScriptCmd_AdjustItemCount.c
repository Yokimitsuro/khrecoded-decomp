#include "nitro/types.h"

typedef struct {
    u16 itemId;
    u8 param1;
    u8 param2;
} ItemRequest;

extern int ScriptVm_ReadOperandInt(void *vm, void *operand);
extern void func_ov001_02064a38(ItemRequest *request, int flags);
extern void func_ov001_02064aa8(ItemRequest *request);

BOOL ScriptCmd_AdjustItemCount(void *vm, u8 *operands)
{
    ItemRequest request;
    int i;
    int count;

    request.itemId = ScriptVm_ReadOperandInt(vm, operands);
    request.param1 = ScriptVm_ReadOperandInt(vm, operands + 8);
    request.param2 = ScriptVm_ReadOperandInt(vm, operands + 0x10);
    count = ScriptVm_ReadOperandInt(vm, operands + 0x18);
    if (count > 0) {
        for (i = 0; i < count; i++) {
            func_ov001_02064a38(&request, 0);
        }
    } else if (count < 0) {
        int removals = -count;
        for (i = 0; i < removals; i++) {
            func_ov001_02064aa8(&request);
        }
    }
    return TRUE;
}
