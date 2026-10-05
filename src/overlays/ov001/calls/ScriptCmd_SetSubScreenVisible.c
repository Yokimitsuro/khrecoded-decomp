#include "nitro/types.h"
#include "nitro/hw.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *context, ScriptOperand *operand);

static inline void SetSubVisiblePlane(u32 planeMask)
{
    *(vu32 *)REG_DB_DISPCNT_ADDR = (*(vu32 *)REG_DB_DISPCNT_ADDR & ~0x1f00) | (planeMask << 8);
}

int ScriptCmd_SetSubScreenVisible(void *context, ScriptOperand *operands)
{
    BOOL visible = ScriptVm_ReadOperandInt(context, operands) ? TRUE : FALSE;

    if (visible) {
        SetSubVisiblePlane(0x1f);
    } else {
        SetSubVisiblePlane(0);
    }
    return 1;
}
