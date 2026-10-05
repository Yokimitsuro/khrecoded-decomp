#include "nitro/types.h"

typedef struct Actor {
    u8 pad_000[0xef4];
    u32 flags;
    u8 pad_ef8[0xf2c - 0xef8];
} Actor;

typedef struct ActorManager {
    u8 pad_0000[0x115c];
    Actor actors[1];
} ActorManager;

extern ActorManager *data_ov001_020a0500;

extern void Actor_AttachSource(Actor *actor, int mode, void *source);
extern void func_ov001_0208a574(Actor *actor, char *motionName, int motionId, int layer, int frameCount);

void PlayIndexedActorMotion(int index, int motionId, int frameCount, char *motionName)
{
    if (data_ov001_020a0500->actors[index].flags == 0) {
        Actor_AttachSource(&data_ov001_020a0500->actors[index], index, NULL);
    }
    func_ov001_0208a574(&data_ov001_020a0500->actors[index], motionName, motionId, 0, frameCount);
}
