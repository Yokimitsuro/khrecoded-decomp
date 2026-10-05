#include "nitro/types.h"

#define REG_POWCNT1 (*(volatile u16 *)0x04000304)

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt(void *context, ScriptOperand *operand);
extern int DispatchPartyEntryByMode(int index);
extern void WriteSessionPackedBits(int bitOffset, u32 bitCount, u32 value);
extern void PushVramState(void);

int ScriptCmd_SetScreenSwap(void *context, ScriptOperand *operands)
{
    switch (ScriptVm_ReadOperandInt(context, operands)) {
    case 0:
        REG_POWCNT1 = REG_POWCNT1 | 0x8000;
        break;
    case 1:
        REG_POWCNT1 = REG_POWCNT1 & ~0x8000;
        break;
    }
    WriteSessionPackedBits(0x351f, 1, DispatchPartyEntryByMode(0));
    PushVramState();
    return 1;
}
