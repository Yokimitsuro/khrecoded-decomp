#include "nitro/types.h"

extern s32 func_ov001_02063a38(void);
extern void *func_ov030_020bb374(void);
extern void *GetSubStruct1C(void);

static inline BOOL IsGameMode(s32 mode)
{
    return func_ov001_02063a38() == mode;
}

void *GetModeContext(void)
{
    if (IsGameMode(4)) {
        return func_ov030_020bb374();
    }
    if (IsGameMode(7)) {
        return GetSubStruct1C();
    }
    return NULL;
}
