#include "nitro/types.h"

typedef struct ActorManager {
    u8 pad_000[0x95C];
    void *actorSlots[0x200];
    u8 partyMembers[3][0xF2C];
} ActorManager;

extern ActorManager *data_ov001_020a0500;
extern void MI_CpuFill8(void *dst, int val, u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void ActorObject_ReleaseResources(void *actor);
extern void Actor_RestoreAnimState(void *actor, s32 flag);

void ClearAllActorSlots(void)
{
    s32 index;
    void *actor;

    index = 0;
    do {
        actor = data_ov001_020a0500->actorSlots[index];
        if (actor != 0) {
            Actor_RestoreAnimState(actor, 0);
            ActorObject_ReleaseResources(data_ov001_020a0500->actorSlots[index]);
            NNSi_FndFreeFromDefaultHeap(data_ov001_020a0500->actorSlots[index]);
            data_ov001_020a0500->actorSlots[index] = 0;
        }
        index = index + 1;
    } while (index < 0x200);
    index = 0;
    do {
        ActorObject_ReleaseResources(data_ov001_020a0500->partyMembers[index]);
        index = index + 1;
    } while (index < 3);
    MI_CpuFill8(data_ov001_020a0500->partyMembers[0], 0, 0x2D84);
}
