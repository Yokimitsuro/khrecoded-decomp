#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Actor Actor;
typedef void (*ActorStateFunc)(Actor *actor, int state);

struct Actor {
    u8 pad_0000[0x928];
    u64 statusFlags;
    u8 playerIndex;
    u8 pad_0931[0x964 - 0x931];
    VecFx32 jointPosition;
    u8 pad_0970[0x170c - 0x970];
    int commands[1];
    u8 pad_1710;
    s8 commandIndex;
    u8 pad_1712[0x171c - 0x1712];
    u32 pad_bits : 14;
    s32 commandActive : 1;
    u32 rest_bits : 17;
    u8 pad_1720[0x1808 - 0x1720];
    ActorStateFunc setState;
};

extern void *func_ov001_0206db78(u8 index);
extern void Actor_GetRotatedJointPosition(VecFx32 *out, Actor *actor);
extern BOOL HasFlagsAt0xe(void *holder, u16 mask);
extern void func_ov059_020c9a74(Actor *actor, int arg);
extern void func_ov059_020c9d34(Actor *actor);
extern void Actor_ConsumeCommand(Actor *actor);

void Actor_UpdateCommandInput(Actor *actor) {
    void *input = func_ov001_0206db78(actor->playerIndex);
    VecFx32 pos;

    Actor_GetRotatedJointPosition(&pos, actor);
    actor->jointPosition = pos;
    if (actor->commandActive && (!HasFlagsAt0xe(input, 0x400) || HasFlagsAt0xe(input, 1))) {
        func_ov059_020c9a74(actor, 0);
    }
    if (actor->commandActive) {
        int command;
        func_ov059_020c9d34(actor);
        command = actor->commands[actor->commandIndex];
        if (command == 3 || command == -1) {
            Actor_ConsumeCommand(actor);
        }
    }
    if (actor->statusFlags & 0x10) {
        actor->setState(actor, 8);
        actor->statusFlags &= ~(u64)0x10;
    }
}
