#include "nitro/types.h"

typedef struct Actor Actor;
typedef BOOL (*QueryFunc)(Actor *actor, int arg);
typedef void (*SetModeFunc)(Actor *actor, int mode);

typedef struct {
    int flags;
    u8 pad_04[4];
    u8 *kind;
    u8 pad_0c[0x54];
    void *target;
    int level;
} ObjHandle;

typedef struct {
    u8 pad_00[4];
    int height;
} Anchor;

struct Actor {
    u8 pad_0000[0x228];
    QueryFunc canWait;
    u8 pad_022c[0x234 - 0x22c];
    u32 flags;
    u8 pad_0238[0x330 - 0x238];
    int baseHeight;
    u8 pad_0334[0x9ac - 0x334];
    u64 stateFlags;
    u8 pad_09b4[0xfc8 - 0x9b4];
    ObjHandle handle;
    u8 pad_1030[0x10ec - 0x1030];
    SetModeFunc setMode;
};

extern BOOL IsObjHandleBit0Set(ObjHandle *handle);
extern BOOL IsObjHandleRequirementMet(ObjHandle *handle, int which);
extern int GetObjHandleLevel(ObjHandle *handle, int which);
extern void SetSlotBFromHandler(ObjHandle *handle, int which);
extern void AdvanceObjHandleConfig(ObjHandle *handle, int forced);
extern BOOL TriggerMatchingHandle(ObjHandle *handle, int id, int forced);
extern Anchor *func_ov052_020ceb74(Actor *actor);
extern void BuildApproachChoices(Actor *actor, int forced, int *ids);
extern BOOL IsTargetAboveInRange(Actor *actor);

void ChooseHandleFollowupMode(Actor *actor)
{
    ObjHandle *handle = &actor->handle;
    int forced = FALSE;
    u32 flagSet = actor->flags & 4;
    BOOL waiting;
    int ids[6];
    int i;
    u8 kind;

    if (handle->target != NULL) {
        if (!IsObjHandleBit0Set(handle)) {
            forced = TRUE;
        } else {
            kind = *handle->kind;
            if ((kind == 4 || kind == 9) && IsObjHandleRequirementMet(handle, 0) && !flagSet
                && func_ov052_020ceb74(actor)->height - actor->baseHeight > 0x800) {
                forced = TRUE;
                handle->level = GetObjHandleLevel(handle, 1);
            }
        }
    } else if (!flagSet) {
        forced = TRUE;
    }
    if (actor->stateFlags & 0x100000) {
        SetSlotBFromHandler(&actor->handle, forced);
        actor->stateFlags &= ~(u64)0x100000;
    }
    if (actor->canWait != NULL) {
        waiting = actor->canWait(actor, 0);
    } else {
        waiting = FALSE;
    }
    if (!waiting) {
        AdvanceObjHandleConfig(handle, forced);
        actor->setMode(actor, 0xb);
        return;
    }
    BuildApproachChoices(actor, forced, ids);
    for (i = 0; i < 6; i++) {
        if (ids[i] == -1) {
            break;
        }
        if (TriggerMatchingHandle(handle, ids[i], forced)) {
            actor->setMode(actor, 0xb);
            return;
        }
    }
    if (IsTargetAboveInRange(actor)) {
        actor->setMode(actor, 0xd);
        return;
    }
    AdvanceObjHandleConfig(handle, forced);
    actor->setMode(actor, 0xb);
}
