#include "nitro/types.h"

typedef struct ScriptVm {
    u8 pad_000[0x628];
    s32 skipWait;
} ScriptVm;

extern void func_ov036_020bda00(void);
extern int GetTextWindowStatus(void);
extern u32 func_ov036_020c30f8(void);
extern void func_ov036_020c3374(void);
extern void WriteSessionPackedBits(int bitOffset, u32 bitCount, u32 value);

BOOL ScriptCmd_WaitWindowChoice(ScriptVm *vm)
{
    int status;

    if (vm->skipWait != 0) {
        func_ov036_020bda00();
        return TRUE;
    }
    status = GetTextWindowStatus();
    switch (status) {
    case 0:
        WriteSessionPackedBits(0x3521, 4, func_ov036_020c30f8());
        func_ov036_020bda00();
        return TRUE;
    case 3:
        func_ov036_020c3374();
        break;
    }
    return FALSE;
}
