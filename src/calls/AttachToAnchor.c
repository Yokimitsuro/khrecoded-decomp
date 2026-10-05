#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x18];
    fx32 x;
    fx32 y;
    fx32 z;
    s16 angle;
    u16 velX;
    u16 velY;
    u16 velZ;
} Anchor;

typedef struct {
    u8 pad_00[0xe];
    u16 unk_0E;
    u32 unk_10;
    Anchor *anchor;
    fx32 x;
    fx32 y;
    fx32 z;
    s16 angle;
    u8 pad_26[2];
    u16 *velXPtr;
    u16 *velYPtr;
    u16 *velZPtr;
    u8 pad_34[0xa];
    u8 active;
    u8 pad_3f;
    u8 flag;
    u8 pad_41[7];
    u32 unk_48;
    u8 pad_4c[4];
    u32 unk_50;
    u8 pad_54[4];
    u32 unk_58;
} Something;

void AttachToAnchor(Something *self, u16 unk_0E, u32 unk_10, u8 flag, Anchor *anchor) {
    self->unk_0E = unk_0E;
    self->unk_10 = unk_10;
    self->flag = flag;
    self->active = 1;
    self->anchor = anchor;
    self->x = anchor->x;
    self->y = anchor->y;
    self->z = anchor->z;
    self->angle = anchor->angle;
    self->velXPtr = &anchor->velX;
    self->velYPtr = &anchor->velY;
    self->velZPtr = &anchor->velZ;
    self->unk_48 = 0;
    self->unk_50 = 0;
    self->unk_58 = 0;
    anchor->velX = 0;
    anchor->velY = 0;
    anchor->velZ = 0;
}
