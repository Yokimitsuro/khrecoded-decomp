#include "nitro/types.h"

extern BOOL func_ov001_02063a24(void);
extern s32 func_ov001_02063a38(void);

s32 GetSessionModeOrZero(void)
{
    if (func_ov001_02063a24()) {
        return func_ov001_02063a38();
    }
    return 0;
}
