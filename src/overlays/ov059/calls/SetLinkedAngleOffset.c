#include "nitro/types.h"

typedef struct {
    u32 flags;
    u16 dirty;
    u8 pad_06[0x7a];
    u16 angle;
} LinkedModel;

typedef struct {
    u8 pad_000[0x230];
    LinkedModel *model;
} Entity;

void SetLinkedAngleOffset(Entity *entity, u16 angle)
{
    u16 rotated = angle + 0x8000;
    LinkedModel *model = entity->model;

    if (!(model->flags & 0x20)) {
        model->angle = rotated;
        model->dirty |= 0x20;
    }
}
