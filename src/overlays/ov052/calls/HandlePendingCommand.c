#include "nitro/types.h"

typedef struct {
    u8 pad00[0x4c];
    u16 modeBits : 2;
    u16 flagA : 1;
    u16 flagB : 1;
    u16 flagC : 1;
    u16 padBits : 11;
} ModelGroup;

typedef struct CommandActor CommandActor;
typedef void (*ActorEventFunc)(CommandActor *actor, int event);

struct CommandActor {
    u8 pad_000[0x234];
    u32 modelFlags;
    u8 pad_238[0x9ac - 0x238];
    u64 stateFlags;
    u8 pool;
    u8 pad_9b5[0xfc8 - 0x9b5];
    u8 activeFlags[0x1028 - 0xfc8];
    ModelGroup **linkedGroup;
    u8 pad_102c[4];
    int command;
    s8 memberSlot;
    u8 pad_1035;
    s8 pendingSlot;
    u8 pad_1037[0x10ec - 0x1037];
    ActorEventFunc onEvent;
};

extern void *func_ov001_0206db78(int pool);
extern BOOL func_ov021_020a7524(void *entry);
extern BOOL IsPlayerEntryFlagSet(int player, u32 id);
extern void SetActiveFlags(void *flags, BOOL extra);
extern BOOL IsTargetAboveInRange(CommandActor *actor);
extern BOOL ConsumeActionInterruptFlag(CommandActor *actor);
extern BOOL CanUseMemberSlot(CommandActor *actor, int index);
extern BOOL IsField1078Clear(CommandActor *actor);

BOOL HandlePendingCommand(CommandActor *actor)
{
    u32 grounded = actor->modelFlags & 4;
    void *entry = func_ov001_0206db78(actor->pool);
    BOOL result = FALSE;
    int event;

    switch (actor->command) {
    case 1:
        actor->stateFlags &= ~0x100;
        if (actor->linkedGroup != NULL && !(*actor->linkedGroup)->flagC && IsTargetAboveInRange(actor)) {
            actor->onEvent(actor, 0xd);
        }
        actor->onEvent(actor, 0xc);
        result = TRUE;
        break;
    case 6:
    case 7:
        event = 0;
        if (actor->memberSlot >= 0) {
            if (CanUseMemberSlot(actor, actor->memberSlot)) {
                event = 0x15;
                if (actor->command != 6) {
                    event = 0x18;
                }
            } else {
                actor->memberSlot = -1;
            }
        } else if (actor->pendingSlot >= 0) {
            if (IsField1078Clear(actor)) {
                event = 0x17;
            } else {
                actor->pendingSlot = -1;
            }
        }
        if (event != 0) {
            actor->onEvent(actor, event);
            if (ConsumeActionInterruptFlag(actor)) {
                result = TRUE;
            }
        }
        break;
    case 4:
    case 5:
        SetActiveFlags(actor->activeFlags, actor->command == 5);
        actor->onEvent(actor, 0xc);
        result = TRUE;
        break;
    case 3:
        if (grounded == 0) {
            break;
        }
        actor->onEvent(actor, 2);
        result = TRUE;
        break;
    case 2:
        if (grounded == 0) {
            break;
        }
        if (func_ov021_020a7524(entry) && IsPlayerEntryFlagSet(actor->pool, 10)) {
            actor->onEvent(actor, 8);
        } else if (IsPlayerEntryFlagSet(actor->pool, 0xb)) {
            actor->onEvent(actor, 9);
        }
        result = TRUE;
        break;
    }
    actor->command = 0;
    return result;
}
