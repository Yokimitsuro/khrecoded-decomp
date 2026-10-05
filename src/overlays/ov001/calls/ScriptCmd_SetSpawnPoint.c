#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ScriptContext ScriptContext;

extern int ScriptVm_ReadOperandInt(ScriptContext *context, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32(ScriptContext *context, ScriptOperand *operand);
extern int _s32_div_f(int dividend, int divisor);
extern void StoreSessionSpawnPoint(int index, const VecFx32 *position, u16 angle);

BOOL ScriptCmd_SetSpawnPoint(ScriptContext *context, ScriptOperand *operands)
{
    VecFx32 position;
    int degrees;
    int index;

    position.x = ScriptVm_ReadOperandFx32(context, &operands[0]);
    position.y = ScriptVm_ReadOperandFx32(context, &operands[1]);
    position.z = ScriptVm_ReadOperandFx32(context, &operands[2]);
    degrees = ScriptVm_ReadOperandInt(context, &operands[3]);
    index = ScriptVm_ReadOperandInt(context, &operands[4]);
    StoreSessionSpawnPoint(index, &position, _s32_div_f(degrees << 16, 360));
    return TRUE;
}
