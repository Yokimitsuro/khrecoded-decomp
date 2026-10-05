#include "nitro/types.h"

extern int func_ov001_02063cac(void);
extern BOOL func_ov001_020645c8(u32 flag);
extern int func_ov001_02063a38(void);
extern BOOL ArePartyActorsSettled(void);
extern BOOL Actor_IsIdleWithoutTarget(void);
extern void ClearSessionPackedBit(u32 flag);
extern u32 func_ov021_020af408(void);
extern void InitFieldCameraFromPreset(void);
extern void SetSubModeFrozen(BOOL frozen);
extern void func_ov001_0206e444(int mode);
extern void RefreshMenuEntries(void);
extern void ForwardSubModeEnd(int mode);
extern void *func_ov001_020882d8(void);

void *TryFinishIntroSequence(void)
{
    if (!func_ov001_02063cac()) {
        if (func_ov001_020645c8(0x3527)
            || (func_ov001_02063a38() != 7 && ArePartyActorsSettled())
            || (func_ov001_02063a38() == 7 && Actor_IsIdleWithoutTarget())) {
            ClearSessionPackedBit(0x3309);
            ClearSessionPackedBit(0x3527);
            if (!func_ov021_020af408()) {
                InitFieldCameraFromPreset();
                SetSubModeFrozen(TRUE);
            }
            func_ov001_0206e444(0);
            RefreshMenuEntries();
            ForwardSubModeEnd(0);
            return func_ov001_020882d8;
        }
    }
    return NULL;
}
