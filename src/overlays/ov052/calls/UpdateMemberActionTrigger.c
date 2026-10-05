#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct MemberActor MemberActor;
typedef void (*ActorEventFunc)(MemberActor *actor, int event);
typedef void (*ActorModeFunc)(MemberActor *actor, int mode, int arg);

typedef struct {
    int animId;
    u8 pad_04[0x3c];
    s16 blendIndex;
} MemberEntry;

struct MemberActor {
    u8 pad_000[0x1f8];
    ActorModeFunc onMode;
    u8 pad_1fc[0x760 - 0x1fc];
    int frame;
    u8 pad_764[4];
    int eventFlag;
    u8 pad_76c[0x9ac - 0x76c];
    u64 stateFlags;
    u8 pool;
    u8 pad_9b5[0x9f8 - 0x9b5];
    fx32 moveSpeed;
    u8 pad_9fc[0x1070 - 0x9fc];
    u8 members[8];
    MemberEntry *currentMember;
    u8 pad_107c[0x10ec - 0x107c];
    ActorEventFunc onEvent;
};

extern BOOL IsPlayerEntryFlagSet(int player, u32 id);
extern int FindCurrentMemberIndex(void *members);
extern void ApplyItemRewardEffect(MemberActor *actor, int blendIndex, int animId, int memberIndex, int arg);
extern int func_ov001_02063a38(void);
extern void func_ov001_02078680(void);

void UpdateMemberActionTrigger(MemberActor *actor)
{
    MemberEntry *member = actor->currentMember;

    if (IsPlayerEntryFlagSet(actor->pool, 0x15)) {
        actor->moveSpeed = 0x3000;
    }
    if ((actor->stateFlags & 0x4000) == 0 && actor->frame >= 0x9000) {
        ApplyItemRewardEffect(actor, member->blendIndex, member->animId, FindCurrentMemberIndex(actor->members), 1);
        actor->stateFlags |= 0x4000;
        if (func_ov001_02063a38() == 6) {
            func_ov001_02078680();
        }
    }
    if (actor->eventFlag != 0) {
        actor->moveSpeed = 0;
        actor->stateFlags &= ~0x4000ULL;
        actor->onEvent(actor, 1);
        if (actor->onMode != NULL) {
            actor->onMode(actor, 0, -1);
        }
    }
}
