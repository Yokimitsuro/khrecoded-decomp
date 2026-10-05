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
extern void *func_ov001_02086384(void *table, int entryIndex);
extern void GetOrbitOffsetDegrees(VecFx32 *direction, fx32 angle);
extern u32 func_ov030_020bb374(void);
extern void *AppendPool2Record(void *manager, fx32 x, fx32 y, VecFx32 *direction, u32 context, fx32 rotation, int duration);
extern s64 _ll_mul(s64 a, s64 b);
extern s64 _ll_sdiv(s64 numerator, s64 denominator);
extern void FormatAndQueueMessage(void *obj, const char *format, u32 flags, void *args);

int ScriptCmd_QueueEntryRotationMessage(void *vm, ScriptOperand *operands)
{
    int entryIndex = ScriptVm_ReadOperandInt(vm, operands);
    BOOL enable = ScriptVm_ReadOperandInt(vm, operands + 1) != 0;
    fx32 x = ScriptVm_ReadOperandFx32(vm, operands + 2);
    fx32 y = ScriptVm_ReadOperandFx32(vm, operands + 3);
    fx32 angle = ScriptVm_ReadOperandFx32(vm, operands + 4);
    fx32 rotation = ScriptVm_ReadOperandFx32(vm, operands + 5);
    int duration = ScriptVm_ReadOperandInt(vm, operands + 6);
    void *manager = FindKind4FieldObject();
    void *entry = func_ov001_02086384(manager, entryIndex);
    VecFx32 direction;

    GetOrbitOffsetDegrees(&direction, angle);
    FormatAndQueueMessage(entry, (const char *)2, enable,
        AppendPool2Record(manager, x, y, &direction, func_ov030_020bb374(),
            (fx32)_ll_sdiv(_ll_mul(rotation, 0x3244), 0xb4000), duration));
    return 1;
}
