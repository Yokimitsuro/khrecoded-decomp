#include "nitro/types.h"

typedef struct Vec3 {
    s32 x, y, z;
} Vec3;

typedef struct Actor {
    u8 pad_00[0x38];
    Vec3 position;
    u8 pad_44[0x4f - 0x44];
    u8 state : 3;
    u8 stateHigh : 5;
    u8 pad_50[0x5a - 0x50];
    u16 flags;
    u8 pad_5c[0x6c - 0x5c];
    Vec3 focusPoint;
} Actor;

Vec3 *GetRaisedFocusPoint(Actor *self)
{
    u16 flags = self->flags;
    if (!(flags & 2) && (!(flags & 0x100) || (flags & 0x800)) && self->state == 0) {
        self->focusPoint = self->position;
        self->focusPoint.y += 0x600;
        return &self->focusPoint;
    }
    return NULL;
}
