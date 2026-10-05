#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u32 flags;
    u16 nodeFlags;
    u8 pad_06[0x1e];
    u32 drawMask;
    u8 pad_28[0x58];
    u16 yaw;
} ActorModel;

typedef struct {
    u8 data[0x230];
} AttachedModel;

typedef struct {
    u8 pad_000[0x230];
    ActorModel *model;
    u8 pad_234[0x75c - 0x234];
    s32 state;
    u8 pad_760[0x9ac - 0x760];
    u64 flags;
    u8 entryId;
    u8 pad_9b5[0xa00 - 0x9b5];
    VecFx32 homePos;
    u8 pad_a0c[0xb68 - 0xa0c];
    AttachedModel parts[2];
    u8 pad_fc8[0x105c - 0xfc8];
    u8 shadow[0x1070 - 0x105c];
    u8 members[0x1108 - 0x1070];
    u8 slotMarker[4];
} DrawnActor;

extern BOOL AnySubObjectFlagsActive(DrawnActor *actor);
extern void func_01ffb12c(void *node);
extern VecFx32 GetAttachmentWorldPosition(DrawnActor *actor, int joint);
extern void DrawPendingSlotModel(DrawnActor *actor, void *shadow);
extern void DrawModelWithAttachment(AttachedModel *model);
extern void DrawSlotMarker(void *marker);
extern void InvokeMemberDrawCallbacks(void *container);
extern void func_ov021_020a8b64(int screen);

void DrawCarriedActor(DrawnActor *actor)
{
    BOOL tilt = FALSE;
    int yaw = actor->model->yaw;
    int delta;
    u16 tiltedYaw;
    u32 mask;
    int i;
    ActorModel *model;

    switch (actor->state) {
    case 0:
        if (AnySubObjectFlagsActive(actor)) {
            break;
        }
        delta = 0x1fff;
        tilt = TRUE;
        break;
    case 5:
    case 11:
    case 12:
        if (yaw >= 0x8000) {
            if (AnySubObjectFlagsActive(actor)) {
                delta = -0xe38;
            } else {
                delta = 0x1fff;
            }
        } else {
            delta = 0x1555;
        }
        tilt = TRUE;
        break;
    case 2:
        delta = 0x1fff;
        if (yaw >= 0x8000 && AnySubObjectFlagsActive(actor)) {
            delta = -0xe38;
        }
        tilt = TRUE;
        break;
    }
    if (tilt && actor->state != 0xf && yaw == 0x8000) {
        tilt = FALSE;
    }
    if (tilt) {
        if (yaw >= 0x8000) {
            tiltedYaw = yaw + delta;
        } else {
            tiltedYaw = yaw - delta;
        }
    }
    mask = 1;
    if (actor->flags & 0x40000) {
        mask |= 2;
    }
    if (tilt) {
        model = actor->model;
        if (!(model->flags & 0x20)) {
            model->yaw = tiltedYaw;
            model->nodeFlags |= 0x20;
        }
    }
    actor->model->drawMask |= mask;
    if (!(actor->model->flags & 0x20)) {
        func_01ffb12c(&actor->model->nodeFlags);
    }
    actor->model->drawMask &= ~mask;
    if (tilt) {
        model = actor->model;
        if (!(model->flags & 0x20)) {
            model->yaw = yaw;
            model->nodeFlags |= 0x20;
        }
    }
    actor->homePos = GetAttachmentWorldPosition(actor, 3);
    if (!(actor->flags & 0x40000)) {
        DrawPendingSlotModel(actor, actor->shadow);
        for (i = 0; i < 2; i++) {
            DrawModelWithAttachment(&actor->parts[i]);
        }
        DrawSlotMarker(actor->slotMarker);
    }
    InvokeMemberDrawCallbacks(actor->members);
    func_ov021_020a8b64(actor->entryId);
}
