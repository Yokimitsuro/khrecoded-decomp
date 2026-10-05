#include "nitro/types.h"

typedef struct ActorManager {
    u8 pad_000[0x764];
    s32 actorCount;
} ActorManager;

extern ActorManager *data_ov001_020a0500;

BOOL IsActorCountNonzero(void)
{
    if (data_ov001_020a0500->actorCount != 0) {
        return TRUE;
    }
    return FALSE;
}
