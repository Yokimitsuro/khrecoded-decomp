#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Actor Actor;
typedef int (*ActorGetMode)(Actor *actor);
typedef void (*ActorNotifyFunc)(Actor *actor, fx32 frame);
typedef void (*ActorStateFunc)(Actor *actor, int state);

struct Actor {
    u8 pad_0000[0x1dc];
    int mode;
    u8 pad_01e0[0x1fc - 0x1e0];
    ActorNotifyFunc onChargeReady;
    u8 pad_0200[0x22c - 0x200];
    ActorGetMode getMode;
    u8 pad_0230[0x234 - 0x230];
    u32 flags;
    u8 pad_0238[0x760 - 0x238];
    fx32 animFrame;
    u8 pad_0764[0x930 - 0x764];
    u8 playerIndex;
    u8 pad_0931[0x948 - 0x931];
    fx32 chargeTime;
    u8 pad_094c[0x1808 - 0x94c];
    ActorStateFunc setState;
};

extern void *func_ov001_0206db78(u8 index);
extern void func_ov059_020c999c(Actor *actor);
extern BOOL IsPlayerEntryFlagSet(int player, u32 id);
extern BOOL func_ov021_020a753c(void *holder, u16 mask);
extern void func_ov059_020ca35c(Actor *actor, int arg1, int arg2);

static inline int Actor_GetMode(Actor *actor) {
    if (actor->getMode != NULL) {
        return actor->getMode(actor);
    }
    return actor->mode;
}

void Actor_UpdateChargeState(Actor *actor) {
    BOOL release = FALSE;
    void *input;
    u32 heavy;
    fx32 charge;

    input = func_ov001_0206db78(actor->playerIndex);
    heavy = actor->flags & 4;
    charge = actor->chargeTime;

    func_ov059_020c999c(actor);
    if (Actor_GetMode(actor) != 4 && IsPlayerEntryFlagSet(actor->playerIndex, 15) && func_ov021_020a753c(input, 2)) {
        actor->setState(actor, 14);
        return;
    }
    func_ov059_020ca35c(actor, 0, 0);
    if (actor->animFrame >= 0x9000 && actor->onChargeReady != NULL) {
        actor->onChargeReady(actor, 0x9000);
    }
    if (charge >= 0x3000 && heavy != 0) {
        release = TRUE;
    } else if (charge >= 0x20000) {
        release = TRUE;
    }
    if (release) {
        if (heavy != 0) {
            actor->setState(actor, 4);
        } else {
            actor->setState(actor, 3);
        }
    }
}
