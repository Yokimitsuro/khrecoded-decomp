#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s8 slot;
    u8 pad1[0x1b];
    u8 disabled : 1;
} HitShape;

typedef struct {
    u8 pad0[0xc];
    int startFrame;
    u8 pad10[0x14];
    HitShape shape;
} HitEvent;

typedef struct {
    u8 pad0[0x18];
    u16 flags;
} HitContext;

typedef int (*HitCallback)(int entity, VecFx32 *offset, HitEvent *event, HitContext *context);

extern void GetAttachmentWorldPosition(VecFx32 *out, int entity, int slot);

int DispatchHitEvent(int entity, HitEvent *event, int unused, HitContext *context)
{
    HitShape *shape = &event->shape;
    int result = 0;
    VecFx32 offset;
    HitCallback callback;
    int slot;
    if (event->startFrame > *(int *)(entity + 0x760) || shape->disabled) {
        return 0;
    }
    offset.z = 0;
    offset.y = 0;
    offset.x = 0;
    slot = shape->slot;
    if (slot < 2 && slot >= 0) {
        GetAttachmentWorldPosition(&offset, entity, slot);
    }
    callback = *(HitCallback *)(entity + 0x10f8);
    if (callback != NULL) {
        result = callback(entity, &offset, event, context);
        context->flags |= 8;
    }
    return result;
}
