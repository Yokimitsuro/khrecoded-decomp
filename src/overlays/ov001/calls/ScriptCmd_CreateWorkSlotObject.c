#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ScriptContext ScriptContext;

typedef struct FieldObjectDesc {
    s16 actorKind;
    s8 unk_02;
    u8 unk_03;
} FieldObjectDesc;

extern int ScriptVm_ReadOperandInt(ScriptContext *context, ScriptOperand *operand);
extern void *CreateWorkSlotObjectClass(u16 count, const FieldObjectDesc *desc);
extern void func_ov001_0207ee2c(int index, void *entry);

BOOL ScriptCmd_CreateWorkSlotObject(ScriptContext *context, ScriptOperand *operands)
{
    int slot;
    int count;
    FieldObjectDesc desc;

    slot = ScriptVm_ReadOperandInt(context, &operands[0]);
    count = ScriptVm_ReadOperandInt(context, &operands[1]);
    desc.actorKind = ScriptVm_ReadOperandInt(context, &operands[2]);
    desc.unk_02 = ScriptVm_ReadOperandInt(context, &operands[3]);
    desc.unk_03 = ScriptVm_ReadOperandInt(context, &operands[4]);
    func_ov001_0207ee2c(slot, CreateWorkSlotObjectClass(count, &desc));
    return TRUE;
}
