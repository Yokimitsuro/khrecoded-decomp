#include "nitro/types.h"

typedef struct ScriptOperand {
    u32 words[2];
} ScriptOperand;

typedef struct ScriptVm {
    u8 pad_000[0x628];
    s32 skipWait;
} ScriptVm;

typedef struct PanelPoint {
    s32 x;
    s32 y;
} PanelPoint;

extern int ScriptVm_ReadOperandInt(ScriptVm *vm, ScriptOperand *operand);
extern int GetLanguageIndex(void);
extern void SetPanelCursorOverride(s32 selection, PanelPoint *position);

BOOL ScriptCmd_SetCursorOverride(ScriptVm *vm, ScriptOperand *operands)
{
    int target = ScriptVm_ReadOperandInt(vm, &operands[0]);
    int selection = ScriptVm_ReadOperandInt(vm, &operands[1]);
    PanelPoint position;

    position.x = ScriptVm_ReadOperandInt(vm, &operands[2]);
    position.y = ScriptVm_ReadOperandInt(vm, &operands[3]);
    if (vm->skipWait != 0) {
        return TRUE;
    }
    if (target != GetLanguageIndex() - 1) {
        return TRUE;
    }
    SetPanelCursorOverride(selection, &position);
    return TRUE;
}
