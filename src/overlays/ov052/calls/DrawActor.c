#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u32 flags;
    u8 node[0x20];
    u32 renderFlags;
} ActorModel;

typedef struct {
    u8 pad_000[0x230];
    ActorModel *model;
    u8 pad_234[0x9ac - 0x234];
    u64 stateFlags;
    u8 pool;
    u8 pad_9b5[0xa00 - 0x9b5];
    VecFx32 attachPosition;
    u8 pad_a0c[0xb68 - 0xa0c];
    u8 parts[2][0x230];
    u8 pad_fc8[0x105c - 0xfc8];
    u8 pendingRequest[0x14];
    u8 members[0x98];
    u8 marker[4];
} DrawnActor;

extern void func_01ffb12c(void *node);
extern VecFx32 GetSlot3WorldPosition(DrawnActor *actor);
extern void DrawPendingSlotModel(DrawnActor *actor, void *request);
extern void DrawModelWithAttachment(void *part);
extern void DrawSlotMarker(void *marker);
extern void UpdateActorShadow(DrawnActor *actor);
extern void InvokeMemberDrawCallbacks(void *members);
extern void func_ov021_020a8b64(int pool);

void DrawActor(DrawnActor *actor)
{
    u32 mask = 1;
    int i;

    if ((actor->stateFlags & 0x40000) != 0) {
        mask |= 2;
    }
    actor->model->renderFlags |= mask;
    if (!(actor->model->flags & 0x20)) {
        func_01ffb12c(actor->model->node);
    }
    actor->model->renderFlags &= ~mask;
    actor->attachPosition = GetSlot3WorldPosition(actor);
    if ((actor->stateFlags & 0x40000) == 0) {
        DrawPendingSlotModel(actor, actor->pendingRequest);
        for (i = 0; i < 2; i++) {
            DrawModelWithAttachment(actor->parts[i]);
        }
        DrawSlotMarker(actor->marker);
        UpdateActorShadow(actor);
    }
    InvokeMemberDrawCallbacks(actor->members);
    func_ov021_020a8b64(actor->pool);
}
