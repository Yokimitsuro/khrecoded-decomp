#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad;
    s32 value;
} ScriptOperand;

extern fx32 ScriptVm_ReadOperandFx32(void *scriptContext, ScriptOperand *operand);
extern int ScriptVm_ReadOperandInt(void *scriptContext, ScriptOperand *operand);
extern ScriptOperand *ScriptVm_ResolveOperand(void *scriptContext, ScriptOperand *operand);
extern int ScriptCmd_ReturnValue(void *scriptContext, int actorId);
extern void *ByteCode_ResolveOperand(void *scriptContext, ScriptOperand *operand);
extern u8 *FindWorldCollisionEntry(void *name);
extern void VEC_Add(const VecFx32 *left, const VecFx32 *right, VecFx32 *result);
extern void SetCameraTargetParams(int mode, int distance, const VecFx32 *focus, const VecFx32 *offset);
extern const VecFx32 data_0205344c;

int ScriptCmd_SetCameraTarget(void *scriptContext, ScriptOperand *operands) {
    VecFx32 zero = data_0205344c;
    VecFx32 focus = zero;
    VecFx32 angles = zero;
    fx32 distance;
    int mode;
    ScriptOperand *operand;
    int degrees;
    u8 *entry;

    distance = ScriptVm_ReadOperandFx32(scriptContext, operands + 4);
    mode = 0;
    focus.x = ScriptVm_ReadOperandFx32(scriptContext, operands + 1);
    focus.y = ScriptVm_ReadOperandFx32(scriptContext, operands + 2);
    focus.z = ScriptVm_ReadOperandFx32(scriptContext, operands + 3);
    operand = ScriptVm_ResolveOperand(scriptContext, operands + 5);
    if (operand->type == 1) {
        angles.x = ScriptVm_ReadOperandInt(scriptContext, operand) * 0xb6;
    }
    operand = ScriptVm_ResolveOperand(scriptContext, operands + 6);
    if (operand->type == 1) {
        degrees = ScriptVm_ReadOperandInt(scriptContext, operand);
        if (degrees > 360) {
            degrees = -(degrees - 360);
        }
        angles.y = degrees * 0xb6;
    }
    operand = ScriptVm_ResolveOperand(scriptContext, operands);
    switch (operand->type) {
    case 1:
        if (operand->value != -1) {
            mode = ScriptCmd_ReturnValue(scriptContext, operand->value);
        } else {
            mode = -1;
        }
        break;
    case 2:
        entry = FindWorldCollisionEntry(ByteCode_ResolveOperand(scriptContext, operand));
        mode = -1;
        VEC_Add(&focus, (VecFx32 *)(entry + 8), &focus);
        break;
    }
    SetCameraTargetParams(mode, distance, &focus, &angles);
    return 1;
}
