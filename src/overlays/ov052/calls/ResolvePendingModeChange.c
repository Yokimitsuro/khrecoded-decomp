#include "nitro/types.h"

typedef struct ModeActor ModeActor;
typedef void (*ModeHookFunc)(ModeActor *actor, int arg, int value);
typedef void (*SetModeFunc)(ModeActor *actor, int mode);

struct ModeActor {
    u8 pad_0000[0x1f8];
    ModeHookFunc onModeExit;
    u8 pad_01fc[0x234 - 0x1fc];
    u32 flags;
    u8 pad_0238[0x75c - 0x238];
    int mode;
    u8 pad_0760[0x768 - 0x760];
    BOOL modeChangePending;
    u8 pad_076c[0x10ec - 0x76c];
    SetModeFunc setMode;
};

void ResolvePendingModeChange(ModeActor *actor)
{
    u32 flagSet = actor->flags & 4;

    if (actor->mode != 0x15) {
        if (flagSet) {
            actor->modeChangePending = TRUE;
        }
    } else if (!flagSet) {
        actor->modeChangePending = TRUE;
    }
    if (actor->modeChangePending) {
        if (flagSet) {
            if (actor->mode != 0x16) {
                if (actor->onModeExit != NULL) {
                    actor->onModeExit(actor, 0, -1);
                }
                actor->setMode(actor, 1);
            } else {
                actor->setMode(actor, 5);
            }
        } else {
            actor->setMode(actor, 4);
        }
    }
}
