#include "nitro/types.h"

extern BOOL func_ov001_020645c8(u32 flag);
extern void func_ov001_02087804(void);
extern void func_ov001_0208781c(void);

u32 ScriptOp_InitSubsystemIfFlagClear(void)
{
    BOOL flagSet;

    flagSet = func_ov001_020645c8(0x3528);
    if (flagSet == 0) {
        func_ov001_02087804();
        func_ov001_0208781c();
    }
    return 1;
}
