#include "nitro/types.h"

typedef struct OperandCmd {
    s16 mode;
    s16 sel;
    s32 field;
} OperandCmd;

typedef struct ScriptFrame {
    u8 pad_00[0x14];
    u8 *table;
    u8 pad_18[0x58];
} ScriptFrame;

typedef struct ScriptObj {
    u8 pad_000[4];
    ScriptFrame frames[4];
    u8 pad_1c4_[0x1c4 - 4 - 4 * 0x70];
    s32 currentIndex;
} ScriptObj;

extern OperandCmd *ScriptVm_ResolveOperand(ScriptObj *obj, OperandCmd *cmd);

u8 *ScriptVm_ReadTableOffsetPtr(ScriptObj *vm, OperandCmd *cmd) {
    ScriptFrame *frame = &vm->frames[vm->currentIndex];
    OperandCmd *operand = ScriptVm_ResolveOperand(vm, cmd);
    return frame->table + *(int *)(frame->table + operand->field);
}
