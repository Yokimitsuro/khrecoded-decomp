#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Actor Actor;
typedef BOOL (*QueryFunc)(Actor *actor, int arg);
typedef void (*SetModeFunc)(Actor *actor, int mode);
typedef void (*ExitFunc)(Actor *actor, int arg, int value);

typedef struct {
    u8 pad0[0x3c];
    u32 flags;
} Target;

typedef struct {
    u8 pad0[0xc];
    VecFx32 position;
    u16 flags;
    u8 pad1a[6];
} SlotEntry;

typedef struct {
    int flags;
    u8 pad_04[0x5c];
    Target **target;
} ObjHandle;

struct Actor {
    u8 pad_0000[0x1f8];
    ExitFunc onModeExit;
    u8 pad_01fc[0x228 - 0x1fc];
    QueryFunc canWait;
    u8 pad_022c[0x234 - 0x22c];
    u32 flags;
    u8 pad_0238[0x768 - 0x238];
    BOOL modeChangePending;
    u8 pad_076c[0x9ac - 0x76c];
    u64 stateFlags;
    u8 player;
    u8 pad_09b5[0xfc8 - 0x9b5];
    ObjHandle handle;
    u8 pad_102c[0x1048 - 0x102c];
    u8 waitTarget[0x10ec - 0x1048];
    SetModeFunc setMode;
};

extern BOOL IsFlag10Set(int *flags);
extern BOOL IsObjHandleBit0Set(int *flags);
extern BOOL IsPlayerEntryFlagSet(int player, u32 id);
extern VecFx32 *GetWaitTargetPosition(void *wait);
extern void func_ov052_020cfdd4(Actor *actor, Target *target, BOOL mirrored);
extern void ApplyAnimRootMotion(Actor *actor, Target *target);
extern void func_ov052_020d1a18(SlotEntry *entry, Target *source, int mirrored, int player);
extern BOOL ProcessTargetHitEntries(Actor *actor, Target *target, SlotEntry *entry);
extern BOOL UpdateActionPhase(Actor *actor, Target *target, BOOL mirrored);
extern BOOL func_ov052_020d03d8(Actor *actor);

void UpdateTargetSlotsAndMode(Actor *actor)
{
    ObjHandle *handle = &actor->handle;
    Target *target = *handle->target;
    BOOL mirrored = IsFlag10Set(&handle->flags);
    SlotEntry entry;
    BOOL waiting;
    u32 flagSet;

    func_ov052_020cfdd4(actor, target, mirrored);
    ApplyAnimRootMotion(actor, target);
    func_ov052_020d1a18(&entry, target, mirrored, actor->player);
    entry.flags |= 0x100;
    if (ProcessTargetHitEntries(actor, target, &entry)) {
        return;
    }
    if (actor->canWait != NULL) {
        waiting = actor->canWait(actor, 0);
    } else {
        waiting = FALSE;
    }
    if (waiting && IsPlayerEntryFlagSet(actor->player, 0x30)) {
        entry.flags |= 2;
        entry.position = *GetWaitTargetPosition(actor->waitTarget);
        ProcessTargetHitEntries(actor, target, &entry);
    }
    if (UpdateActionPhase(actor, target, mirrored)) {
        return;
    }
    if (!actor->modeChangePending) {
        return;
    }
    flagSet = actor->flags & 4;
    if (func_ov052_020d03d8(actor)) {
        return;
    }
    if (flagSet) {
        if (IsObjHandleBit0Set(&handle->flags) && !(target->flags & 4)) {
            actor->setMode(actor, 1);
            if (actor->onModeExit != NULL) {
                actor->onModeExit(actor, 0, -1);
            }
            return;
        }
        actor->setMode(actor, 5);
        return;
    }
    if (!IsObjHandleBit0Set(&handle->flags)) {
        actor->stateFlags |= 0x100;
    }
    actor->setMode(actor, 4);
}
