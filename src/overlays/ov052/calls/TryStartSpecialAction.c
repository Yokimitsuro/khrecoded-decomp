#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ActionActor ActionActor;
typedef void (*ActorEventFunc)(ActionActor *actor, int event);
typedef BOOL (*ActorCheckFunc)(ActionActor *actor);

typedef struct {
    u8 pad_00[0x34];
    int cooldown;
    int busy;
    u8 pad_3c[3];
    s8 useCount;
} ActionState;

struct ActionActor {
    u8 pad_000[0x234];
    u32 modelFlags;
    u8 pad_238[0x9ac - 0x238];
    u64 stateFlags;
    u8 pool;
    u8 pad_9b5[0xa10 - 0x9b5];
    ActionState action;
    u8 pad_a50[0x10ec - 0xa50];
    ActorEventFunc onEvent;
    u8 pad_10f0[0x10fc - 0x10f0];
    ActorCheckFunc tryAction;
};

extern void *func_ov001_0206db78(int pool);
extern BOOL func_ov001_02072040(void);
extern BOOL func_ov001_0206e2b0(void);
extern BOOL func_ov021_020a753c(void *holder, u16 mask);
extern BOOL func_ov021_020a754c(void *holder, u16 mask);
extern BOOL IsPlayerEntryFlagSet(int player, u32 id);
extern int GetPlayerEntryCount(int player, u32 id);

BOOL TryStartSpecialAction(ActionActor *actor)
{
    void *self = func_ov001_0206db78(actor->pool);
    ActionState *air = &actor->action;
    BOOL result = FALSE;

    if ((actor->stateFlags & 0x8000000) != 0) {
        return result;
    }
    if (func_ov001_02072040()) {
        return actor->tryAction(actor);
    }
    if (actor->modelFlags & 4) {
        return result;
    }
    if (air->cooldown > 0) {
        return result;
    }
    result = actor->tryAction(actor);
    if (!result) {
        if (!func_ov001_0206e2b0() && func_ov021_020a753c(self, 2) && IsPlayerEntryFlagSet(actor->pool, 0xd)
            && air->useCount < GetPlayerEntryCount(actor->pool, 0xd)) {
            actor->onEvent(actor, 0x13);
            result = TRUE;
        }
        if (!result && air->busy == 0 && func_ov021_020a754c(self, 0x800) && IsPlayerEntryFlagSet(actor->pool, 0xe)
            && (actor->stateFlags & 0x8000) == 0) {
            actor->onEvent(actor, 0x11);
            result = TRUE;
        }
    }
    return result;
}
