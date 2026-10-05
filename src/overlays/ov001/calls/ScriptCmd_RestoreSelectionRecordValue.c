#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct OverlaySelectionRecord {
    u8 overlaySet;
    u8 pad_01;
    u16 currentValue;
    u16 savedValue;
} OverlaySelectionRecord;

extern int ScriptVm_ReadOperandInt(void *context, ScriptOperand *operand);
extern OverlaySelectionRecord *GetOverlaySelectionRecord(u32 selectionIndex);

int ScriptCmd_RestoreSelectionRecordValue(void *context, ScriptOperand *operands)
{
    u32 selectionIndex;

    selectionIndex = ScriptVm_ReadOperandInt(context, operands);
    GetOverlaySelectionRecord(selectionIndex)->currentValue =
        GetOverlaySelectionRecord(selectionIndex)->savedValue;
    return 1;
}
