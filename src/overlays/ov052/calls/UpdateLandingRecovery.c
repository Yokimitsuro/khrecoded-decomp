#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct RecoverActor RecoverActor;
typedef void (*ActorEventFunc)(RecoverActor *actor, int event);
typedef void (*ActorModeFunc)(RecoverActor *actor, int mode, int arg);
typedef void (*ActorScaleFunc)(RecoverActor *actor, fx32 scale);

typedef struct {
    u8 pad_00[0x3d];
    s8 locked;
} RecoverState;

struct RecoverActor {
    u8 pad_000[0x1f8];
    ActorModeFunc onMode;
    ActorScaleFunc onScale;
    u8 pad_200[0x234 - 0x200];
    u32 modelFlags;
    u8 pad_238[0x760 - 0x238];
    int frame;
    u8 pad_764[4];
    int eventFlag;
    u8 pad_76c[0x9ac - 0x76c];
    u64 stateFlags;
    u8 pool;
    u8 pad_9b5[0x9c4 - 0x9b5];
    fx32 speed;
    u8 pad_9c8[0xa10 - 0x9c8];
    RecoverState recover;
    u8 pad_a4e[0x10ec - 0xa4e];
    ActorEventFunc onEvent;
};

extern void *func_ov001_0206db78(int pool);
extern BOOL HasFlagsAt0xe(void *holder, u16 mask);

void UpdateLandingRecovery(RecoverActor *actor)
{
    void *self = func_ov001_0206db78(actor->pool);
    RecoverState *recover = &actor->recover;
    u32 grounded = actor->modelFlags & 4;

    if ((actor->stateFlags & 8) != 0) {
        actor->onEvent(actor, 9);
        return;
    }
    if (grounded == 0) {
        actor->onEvent(actor, 4);
        return;
    }
    if (HasFlagsAt0xe(self, 0x800) && recover->locked == 0) {
        if (actor->speed < 0x1e000) {
            if (actor->frame >= 0x11000 && actor->onScale != NULL) {
                actor->onScale(actor, 0x9000);
            }
        } else {
            recover->locked = 1;
        }
    } else {
        recover->locked = 1;
        if (actor->frame < 0x12000 && actor->speed > actor->frame && actor->onScale != NULL) {
            actor->onScale(actor, 0x12000);
        }
    }
    if (actor->eventFlag != 0) {
        actor->onEvent(actor, 1);
        if (actor->onMode != NULL) {
            actor->onMode(actor, 0, -1);
        }
    }
}
