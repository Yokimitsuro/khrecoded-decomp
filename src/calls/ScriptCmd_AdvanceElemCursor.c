#include "nitro/types.h"

typedef struct ScriptObj {
    u8 pad_00[0x1c4];
    s32 currentIndex;
} ScriptObj;

typedef struct ScriptOperandPair {
    s32 first;
    s32 second;
} ScriptOperandPair;

extern s32 *ScriptVm_EvalExpr(ScriptObj *obj, s32 value);

int ScriptCmd_AdvanceElemCursor(ScriptObj *obj, ScriptOperandPair *operands)
{
    u8 *elem = (u8 *)obj + 4 + obj->currentIndex * 0x70;
    s32 *result = ScriptVm_EvalExpr(obj, *(s32 *)(elem + 0x14) + operands->first);
    if (result[1] == 0) {
        *(s32 *)(elem + 0x10) = *(s32 *)(elem + 0xc) + operands->second;
        return 2;
    }
    return 1;
}
