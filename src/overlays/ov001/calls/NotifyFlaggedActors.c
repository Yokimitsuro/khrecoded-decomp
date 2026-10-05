#include "nitro/types.h"

typedef struct ActorManager {
    u8 pad_000[0x95C];
    void *actorSlots[0x200];
} ActorManager;

extern ActorManager *data_ov001_020a0500;
extern s32 IsActorFlagBit8Set(void);
extern void UpdatePartyActorMotion(void *actor);

void NotifyFlaggedActors(void)
{
    s32 index;
    s32 hasFlag;

    index = 0;
    do {
        if (data_ov001_020a0500->actorSlots[index] != 0 &&
            (hasFlag = IsActorFlagBit8Set(), hasFlag != 0)) {
            UpdatePartyActorMotion(data_ov001_020a0500->actorSlots[index]);
        }
        index = index + 1;
    } while (index < 0x200);
}
