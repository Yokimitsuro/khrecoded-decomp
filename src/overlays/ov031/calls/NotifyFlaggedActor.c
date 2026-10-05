#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x5a];
    u8 category;
} ActorInfo;

typedef struct Actor {
    struct Actor *next;
    ActorInfo *info;
    u8 pad_08[0x48];
    u16 flags;
} Actor;

extern Actor *func_ov001_02087264(void);
extern void CallWithZeroFlag(Actor *actor, int arg1, int arg2, int arg3, int arg4, s8 arg5, s8 arg6);

void NotifyFlaggedActor(int target, int value, int offsetX, int offsetY)
{
    Actor *actor;

    for (actor = func_ov001_02087264(); actor != NULL; actor = actor->next) {
        if (actor->info->category == 6 && (actor->flags & 8)) {
            CallWithZeroFlag(actor, target, 2, 0, value, (s8)offsetX, (s8)offsetY);
            return;
        }
    }
}

