#include "nitro/types.h"

typedef struct OperandCmd {
    s16 mode;
    s16 sel;
    s32 field;
} OperandCmd;

typedef struct OperandSlot {
    s16 kind;
    s16 pad;
    s32 value;
} OperandSlot;

typedef struct ScriptElem {
    u8 pad_00[0x14];
    u8 *table;
} ScriptElem;

typedef int (*ScriptHandlerFunc)(u16 lo, u16 hi);

typedef struct ScriptObj {
    u8 pad_00[0x1c4];
    s32 currentIndex;
    u8 pad_1c8[0x618 - 0x1c8];
    OperandSlot scratch;
    u8 pad_620[0x640 - 0x620];
    ScriptHandlerFunc handler;
} ScriptObj;

OperandCmd *ScriptVm_ResolveOperand(ScriptObj *obj, OperandCmd *cmd)
{
    ScriptElem *elem = (ScriptElem *)((u8 *)obj + 4 + obj->currentIndex * 0x70);
    OperandCmd *result;
    int mode = cmd->mode;

    if (mode == 8) {
        result = (OperandCmd *)(elem->table + cmd->field);
    } else if (mode == 4) {
        u32 field;
        obj->scratch.kind = 1;
        field = (u32)cmd->field;
        obj->scratch.value = obj->handler((u16)field, (u16)(field >> 16));
        result = (OperandCmd *)&obj->scratch;
    } else if ((mode & 0x80) == 0) {
        result = cmd;
    } else {
        int sel = cmd->sel;
        int idx;
        if (mode & 4) {
            u32 field = (u32)cmd->field;
            idx = obj->handler((u16)field, (u16)(field >> 16));
        } else if (mode & 8) {
            idx = *(s32 *)(elem->table + cmd->field + 4);
        } else {
            idx = cmd->field;
        }
        obj->scratch.kind = (s16)(cmd->mode & ~0x8c);
        obj->scratch.value = *(s32 *)(elem->table + sel + idx * 4);
        result = (OperandCmd *)&obj->scratch;
    }
    return result;
}
