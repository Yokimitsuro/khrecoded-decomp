#include "nitro/types.h"

typedef struct ReactionActor ReactionActor;

typedef struct {
    u8 pad_00[4];
    s32 threshold;
    s32 progress;
} ReactionEvent;

struct ReactionActor {
    u8 pad_000[0x1fc];
    void (*onThresholdReached)(ReactionActor *actor, int value);
    u8 pad_200[0x9b4 - 0x200];
    u8 entryId;
    u8 pad_9b5[0x9c0 - 0x9b5];
    s32 state;
    u8 pad_9c4[0x10ec - 0x9c4];
    void (*setState)(ReactionActor *actor, int state);
    u8 pad_10f0[0x10fc - 0x10f0];
    int (*checkBusy)(ReactionActor *actor);
};

extern void *func_ov001_0206db78(int index);
extern BOOL func_ov021_020a753c(void *holder, u16 mask);
extern BOOL func_ov021_020a7530(void *holder);
extern BOOL IsPlayerEntryFlagSet(int entryId, int flag);
extern BOOL func_ov052_020cfb78(ReactionActor *actor);
extern BOOL func_ov001_020645c8(int flagId);
extern BOOL func_ov052_020cf008(ReactionActor *actor, ReactionEvent *event);

int UpdateActorReactionState(ReactionActor *actor, ReactionEvent *event)
{
    void *entry = func_ov001_0206db78(actor->entryId);
    int result = actor->checkBusy(actor);

    if (result == 0) {
        if (func_ov021_020a753c(entry, 2)) {
            BOOL reached = FALSE;
            if (event->progress >= event->threshold) {
                reached = TRUE;
            }
            actor->setState(actor, 2);
            if (actor->state == 2) {
                if (reached && actor->onThresholdReached != NULL) {
                    actor->onThresholdReached(actor, 0x1000);
                }
                return 1;
            }
        }
        if (func_ov021_020a753c(entry, 0x800)) {
            if (func_ov021_020a7530(entry) && IsPlayerEntryFlagSet(actor->entryId, 10)) {
                actor->setState(actor, 8);
                return 1;
            }
            if (func_ov052_020cfb78(actor) && !func_ov001_020645c8(0x3520) &&
                IsPlayerEntryFlagSet(actor->entryId, 0xb)) {
                actor->setState(actor, 9);
                return 1;
            }
        }
        if (func_ov052_020cf008(actor, event)) {
            actor->setState(actor, 0x12);
            if (actor->state == 2) {
                return 1;
            }
        }
    }
    return result;
}
