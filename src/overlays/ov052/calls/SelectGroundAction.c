#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct GroundActor GroundActor;
typedef void (*ActorEventFunc)(GroundActor *actor, int event);
typedef void (*ActorScaleFunc)(GroundActor *actor, fx32 scale);
typedef BOOL (*ActorCheckFunc)(GroundActor *actor);

typedef struct {
    u8 pad_00[4];
    int required;
    int current;
} ActionInput;

struct GroundActor {
    u8 pad_000[0x1fc];
    ActorScaleFunc onScale;
    u8 pad_200[0x9b4 - 0x200];
    u8 pool;
    u8 pad_9b5[0x9c0 - 0x9b5];
    int mode;
    u8 pad_9c4[0x10ec - 0x9c4];
    ActorEventFunc onEvent;
    u8 pad_10f0[0x10fc - 0x10f0];
    ActorCheckFunc tryAction;
};

extern void *func_ov001_0206db78(int pool);
extern BOOL func_ov021_020a753c(void *holder, u16 mask);
extern BOOL func_ov021_020a7530(void *holder);
extern BOOL IsPlayerEntryFlagSet(int player, u32 id);
extern BOOL func_ov052_020cfb78(GroundActor *actor);
extern BOOL func_ov001_020645c8(int id);
extern BOOL func_ov052_020cf008(GroundActor *actor, ActionInput *input);
extern BOOL FindDashWallTarget(GroundActor *actor, ActionInput *input);

BOOL SelectGroundAction(GroundActor *actor, ActionInput *input)
{
    void *self = func_ov001_0206db78(actor->pool);
    BOOL result = actor->tryAction(actor);
    BOOL full;

    if (result == FALSE) {
        if (func_ov021_020a753c(self, 2)) {
            full = FALSE;
            if (input->current >= input->required) {
                full = TRUE;
            }
            actor->onEvent(actor, 2);
            if (actor->mode == 2) {
                if (full && actor->onScale != NULL) {
                    actor->onScale(actor, 0x1000);
                }
                return TRUE;
            }
        }
        if (func_ov021_020a753c(self, 0x800)) {
            if (func_ov021_020a7530(self) && IsPlayerEntryFlagSet(actor->pool, 10)) {
                actor->onEvent(actor, 8);
                return TRUE;
            }
            if (func_ov052_020cfb78(actor) && !func_ov001_020645c8(0x3520) && IsPlayerEntryFlagSet(actor->pool, 11)) {
                actor->onEvent(actor, 9);
                return TRUE;
            }
        }
        if (func_ov052_020cf008(actor, input)) {
            actor->onEvent(actor, 0x12);
            if (actor->mode == 2) {
                return TRUE;
            }
        }
        if (FindDashWallTarget(actor, input)) {
            actor->onEvent(actor, 0x10);
            return TRUE;
        }
    }
    return result;
}
