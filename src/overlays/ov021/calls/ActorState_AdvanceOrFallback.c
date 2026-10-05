#include "nitro/types.h"

typedef struct BattleActor BattleActor;
typedef void *(*ActorState)(void);
typedef void (*ActorNotify)(BattleActor *actor, int event, int arg);

struct BattleActor {
    u8 pad_000[0x1f8];
    ActorNotify notify;
    u8 pad_1fc[0x7b8];
    u8 playerId;
    u8 pad_9b5[0x43];
    s32 recoverSpeed;
};

typedef struct {
    u8 pad_00[0x14];
    int actorIndex;
} StateContext;

extern BattleActor *GetBoundedEntryField(int index);
extern ActorState SelectFallStateHandler(BattleActor *actor, s32 *out);
extern void *UpdateMemberActionTrigger(void);
extern BOOL IsPlayerEntryFlagSet(int player, u32 id);

ActorState ActorState_AdvanceOrFallback(StateContext *context, int unused, s32 *out)
{
    BattleActor *actor = GetBoundedEntryField(context->actorIndex);
    ActorState next;

    *out = 0x19;
    next = SelectFallStateHandler(actor, out);
    if (next == NULL) {
        if (IsPlayerEntryFlagSet(actor->playerId, 0x15)) {
            actor->recoverSpeed = 0x3000;
        }
        if (actor->notify != NULL) {
            actor->notify(actor, 0x1e, -1);
        }
        next = UpdateMemberActionTrigger;
    }
    return next;
}
