#include "nitro/types.h"

typedef struct {
    u32 flags;
    u16 dirty;
    u8 pad[0x7a];
    u16 angle;
} LinkedObject;

void SetLinkedAngleIfUnlocked(int entity, int angle)
{
    u16 value = angle + 0x8000;
    LinkedObject *obj = *(LinkedObject **)(entity + 0x230);
    if (!(obj->flags & 0x20)) {
        obj->angle = value;
        obj->dirty |= 0x20;
    }
}
