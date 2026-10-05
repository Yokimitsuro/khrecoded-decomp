#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *vm, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32(void *vm, ScriptOperand *operand);
extern void *FindKind4FieldObject(void);
extern void func_ov017_020a3b08(void *manager, u16 objectId, int slot, u16 packedLow, u8 packedHigh, VecFx32 *position,
                                s8 linkIndex, s8 linkGroup, s16 eventId, int mode, fx32 speed, int modeParam);

int ScriptCmd_CreateManagerObject(void *vm, ScriptOperand *operands)
{
    int objectId = ScriptVm_ReadOperandInt(vm, operands);
    int slot = ScriptVm_ReadOperandInt(vm, operands + 1);
    u32 packed = operands[2].value;
    VecFx32 position;
    fx32 speed;
    int linkIndex;
    int linkGroup;
    int mode;
    int eventId;
    int modeParam;

    position.x = ScriptVm_ReadOperandFx32(vm, operands + 3);
    position.y = ScriptVm_ReadOperandFx32(vm, operands + 4);
    position.z = 0;
    speed = ScriptVm_ReadOperandFx32(vm, operands + 5);
    linkIndex = ScriptVm_ReadOperandInt(vm, operands + 6);
    linkGroup = ScriptVm_ReadOperandInt(vm, operands + 7);
    mode = ScriptVm_ReadOperandInt(vm, operands + 8);
    eventId = ScriptVm_ReadOperandInt(vm, operands + 9);
    modeParam = ScriptVm_ReadOperandInt(vm, operands + 10);

    func_ov017_020a3b08(FindKind4FieldObject(), objectId, slot, packed, (u16)(packed >> 16), &position,
                        linkIndex, linkGroup, eventId, mode, speed, modeParam);
    return 1;
}
