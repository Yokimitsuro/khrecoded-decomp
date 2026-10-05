#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *vm, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32(void *vm, ScriptOperand *operand);
extern VecFx32 GetOrbitOffsetDegrees(fx32 angle);
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);
extern void *FindKind4FieldObject(void);
extern void *func_ov001_02086384(void *table, int entryIndex);
extern void *AppendPool3Entry(void *manager, VecFx32 *vec);
extern void FormatAndQueueMessage(void *obj, const char *format, u32 flags, void *args);

static inline VecFx32 ScaleVec(VecFx32 vec, fx32 scale)
{
    ScaleVecFx32InPlace(&vec, scale);
    return vec;
}

int ScriptCmd_QueueEntryDirectionMessage(void *vm, ScriptOperand *operands)
{
    int entryIndex = ScriptVm_ReadOperandInt(vm, operands);
    BOOL enable = ScriptVm_ReadOperandInt(vm, operands + 1) != 0;
    fx32 angle = ScriptVm_ReadOperandFx32(vm, operands + 2);
    fx32 length = ScriptVm_ReadOperandFx32(vm, operands + 3);
    VecFx32 direction = ScaleVec(GetOrbitOffsetDegrees(angle), length);
    void *manager = FindKind4FieldObject();
    void *entry = func_ov001_02086384(manager, entryIndex);

    FormatAndQueueMessage(entry, (const char *)3, enable, AppendPool3Entry(manager, &direction));
    return 1;
}
