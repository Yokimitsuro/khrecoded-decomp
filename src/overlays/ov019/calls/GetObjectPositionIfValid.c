#include "nitro/types.h"

typedef struct Vec3 {
    s32 x, y, z;
} Vec3;

typedef struct Actor {
    u8 pad_00[0x38];
    Vec3 position;
    u8 pad_44[0x4f - 0x44];
    u8 lowBits : 6;
    u8 hasPosition : 1;
    u8 highBit : 1;
} Actor;

BOOL GetObjectPositionIfValid(Actor *self, Vec3 *out)
{
    if (self->hasPosition) {
        *out = self->position;
        return TRUE;
    }
    return FALSE;
}
