#include "nitro/types.h"

typedef struct Actor Actor;

typedef struct RewardWork {
    u8 pad_0000[0x1274];
    int rewardKind;
    s16 rewardGroups[1];
} RewardWork;

struct Actor {
    u8 pad_000[0x1f8];
    void (*onEvent)(Actor *actor, int event, int value);
    u8 pad_1fc[0x760 - 0x1fc];
    int chargeTime;
    u8 pad_764[0x768 - 0x764];
    int isActive;
    u8 pad_76c[0x9ac - 0x76c];
    u64 stateFlags;
    u8 selection;
    u8 pad_9b5[0x9f8 - 0x9b5];
    int boostTime;
    u8 pad_9fc[0x1034 - 0x9fc];
    s8 rewardOrder;
    u8 pad_1035[0x10ec - 0x1035];
    void (*setMode)(Actor *actor, int mode);
};

extern RewardWork *data_ov054_020d3720;
extern BOOL IsPlayerEntryFlagSet(u32 selection, int flag);
extern void func_ov052_020d0ee0(Actor *actor, int groupId, int kind, int order, BOOL openMenu);
extern void *func_ov001_0206db78(u32 selection);
extern u16 SharedObject_GetId(void *self);
extern void func_ov054_020d34d0(Actor *actor, int arg);

void UpdateRewardCharge(Actor *actor)
{
    RewardWork *work = data_ov054_020d3720;

    if (IsPlayerEntryFlagSet(actor->selection, 0x15)) {
        actor->boostTime = 0x3000;
    }
    if ((actor->stateFlags & 0x4000) == 0 && actor->chargeTime >= 0x9000) {
        func_ov052_020d0ee0(actor, work->rewardGroups[work->rewardKind - 0xb7], work->rewardKind, actor->rewardOrder, TRUE);
        actor->stateFlags |= 0x4000;
    }
    if (SharedObject_GetId(func_ov001_0206db78(actor->selection)) == 0) {
        func_ov054_020d34d0(actor, 0);
    }
    if (actor->isActive != 0) {
        actor->boostTime = 0;
        actor->stateFlags &= ~(u64)0x4000;
        actor->setMode(actor, 1);
        if (actor->onEvent != NULL) {
            actor->onEvent(actor, 0, -1);
        }
    }
}
