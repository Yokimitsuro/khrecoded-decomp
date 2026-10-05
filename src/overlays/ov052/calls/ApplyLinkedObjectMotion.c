#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct EventInfo {
    u8 type;
    u8 groupId;
    u8 entryId;
} EventInfo;

typedef struct LinkTarget {
    u8 pad_000[0x194];
    EventInfo event;
} LinkTarget;

typedef struct LinkHolder {
    u8 pad_00[0x14];
    LinkTarget *target;
} LinkHolder;

typedef struct MotionState {
    u8 pad_00[0x10];
    LinkHolder *link;
    u8 pad_14[0xc4 - 0x14];
    int moveMode;
} MotionState;

typedef struct Entity {
    u8 pad_000[0x234];
    u32 statusFlags;
    u8 pad_238[0x274 - 0x238];
    MotionState motion;
    u8 pad_33c[0x9ac - 0x33c];
    u64 stateFlags;
    u8 pad_9b4[0x9c8 - 0x9b4];
    fx32 totalX;
    fx32 totalY;
    fx32 totalZ;
    VecFx32 lastDelta;
} Entity;

extern void *func_ov001_0207f060(u32 groupId, u32 entryId);
extern int ForwardIfWorkMode12(void *task, VecFx32 *delta, EventInfo *event);
extern void *func_ov001_0208724c(u32 groupId, u32 entryId);
extern int func_ov001_020863f4(void *task, VecFx32 *delta);

void ApplyLinkedObjectMotion(Entity *entity)
{
    BOOL moved;
    MotionState *motion = &entity->motion;
    int moveMode;
    LinkTarget *target;
    EventInfo *event;
    VecFx32 delta;

    if ((entity->stateFlags & 0x20) != 0) {
        return;
    }
    moveMode = motion->moveMode;
    if (moveMode == 0) {
        return;
    }
    if ((entity->statusFlags & 4) == 0) {
        return;
    }
    entity->lastDelta.z = 0;
    entity->lastDelta.y = 0;
    entity->lastDelta.x = 0;
    if (moveMode != 1) {
        return;
    }
    target = motion->link->target;
    if (target == NULL) {
        return;
    }
    event = &target->event;
    moved = FALSE;
    switch (event->type) {
    case 2:
        if (ForwardIfWorkMode12(func_ov001_0207f060(event->groupId, event->entryId), &delta, event) != 0) {
            moved = TRUE;
        }
        break;
    case 4:
        if (func_ov001_020863f4(func_ov001_0208724c(event->groupId, event->entryId), &delta) != 0) {
            moved = TRUE;
        }
        break;
    }
    if (!moved) {
        return;
    }
    entity->totalX += delta.x;
    entity->totalZ += delta.z;
    entity->lastDelta = delta;
}
