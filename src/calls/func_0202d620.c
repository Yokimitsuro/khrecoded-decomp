#include "nitro/types.h"

typedef struct UnknownState_02060764 {
    u32 unk_00;
    void *target;
} UnknownState_02060764;

extern UnknownState_02060764 data_02060764;

void func_0202d620(u32 value)
{
    if (data_02060764.target != NULL) {
        *(u32 *)((u8 *)data_02060764.target + 0x600) = value;
    }
}
