#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    u32 value;
} ScriptOperand;

typedef struct ScriptContext ScriptContext;

typedef struct FieldObjectDesc {
    s16 actorKind;
    s8 unk_02;
    s8 unk_03;
    s8 shapeKind;
    u8 pad_05[0x3];
    fx32 sizeX;
    fx32 sizeY;
    fx32 sizeZ;
    u32 unk_14;
    s8 unk_18;
} FieldObjectDesc;

extern int ScriptVm_ReadOperandInt(ScriptContext *context, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32(ScriptContext *context, ScriptOperand *operand);
extern void *CreateEventTriggerClass(u16 count, FieldObjectDesc *desc);
extern void func_ov001_0207ee2c(int index, void *entry);

BOOL ScriptCmd_RegisterTriggerClass(ScriptContext *context, ScriptOperand *operands)
{
    int classIndex = ScriptVm_ReadOperandInt(context, &operands[0]);
    int count = ScriptVm_ReadOperandInt(context, &operands[1]);
    FieldObjectDesc desc;

    desc.actorKind = ScriptVm_ReadOperandInt(context, &operands[2]);
    desc.unk_02 = ScriptVm_ReadOperandInt(context, &operands[3]);
    desc.unk_03 = ScriptVm_ReadOperandInt(context, &operands[4]);
    desc.shapeKind = ScriptVm_ReadOperandInt(context, &operands[5]);
    desc.sizeX = ScriptVm_ReadOperandFx32(context, &operands[6]);
    desc.sizeY = ScriptVm_ReadOperandFx32(context, &operands[7]);
    desc.sizeZ = ScriptVm_ReadOperandFx32(context, &operands[8]);
    desc.unk_14 = ScriptVm_ReadOperandFx32(context, &operands[9]);
    desc.unk_18 = ScriptVm_ReadOperandInt(context, &operands[10]);
    func_ov001_0207ee2c(classIndex, CreateEventTriggerClass(count, &desc));
    return TRUE;
}
