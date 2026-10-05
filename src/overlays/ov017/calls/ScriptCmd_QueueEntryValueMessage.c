#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *vm, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32(void *vm, ScriptOperand *operand);
extern void *func_ov017_020a4224(void);
extern void *func_ov001_02086384(void *table, int entryIndex);
extern void *func_ov017_020a3ee4(void *manager, int value);
extern void func_ov017_020a4028(void *obj, const char *format, u32 flags, void *args);

int ScriptCmd_QueueEntryValueMessage(void *vm, ScriptOperand *operands)
{
    int entryIndex = ScriptVm_ReadOperandInt(vm, operands);
    BOOL enable = ScriptVm_ReadOperandInt(vm, operands + 1) != 0;
    fx32 value = ScriptVm_ReadOperandFx32(vm, operands + 2);
    void *manager = func_ov017_020a4224();
    void *entry = func_ov001_02086384(manager, entryIndex);

    func_ov017_020a4028(entry, NULL, enable, func_ov017_020a3ee4(manager, value));
    return 1;
}
