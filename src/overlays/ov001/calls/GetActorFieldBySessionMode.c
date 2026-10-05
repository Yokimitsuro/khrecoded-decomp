#include "nitro/types.h"

extern s32 func_ov001_02063a38(void);

void *GetActorFieldBySessionMode(u8 *actor)
{
    s32 sessionMode;

    sessionMode = func_ov001_02063a38();
    if (sessionMode == 7) {
        return actor + 0x9d4;
    }
    return actor + 0xb68;
}
