#include "nitro/types.h"

void MarkPendingActionIfTargetSet(void *actor) {
    if (*(s32 *)((u8 *)actor + 0x624) != 0) {
        *(u32 *)((u8 *)actor + 0x628) = 1;
        *(u32 *)((u8 *)actor + 0x62c) = 0;
    }
}
