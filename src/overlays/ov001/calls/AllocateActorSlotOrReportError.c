#include "nitro/types.h"

extern int func_ov001_0209c5ac(int kind);
extern void func_ov001_0209c5d8(int errorCode);

int AllocateActorSlotOrReportError(void)
{
    if (func_ov001_0209c5ac(1) == 0) {
        func_ov001_0209c5d8(0x30);
        return 3;
    }
    return 0;
}
