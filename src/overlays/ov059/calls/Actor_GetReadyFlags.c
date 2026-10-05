#include "nitro/types.h"

typedef struct {
    u32 flags;
    u16 dirty;
} BodyModel;

typedef struct {
    u8 pad_00[2];
    u16 remaining;
} GaugeState;

typedef struct {
    u8 pad_000[0x1d4];
    GaugeState *gauge;
    u8 pad_1d8[0x230 - 0x1d8];
    BodyModel *body;
    u8 pad_234[0x75c - 0x234];
    s32 motion;
    u8 pad_760[0x928 - 0x760];
    u64 flags;
    u8 pad_930[0x944 - 0x930];
    s32 mode;
} Actor;

u32 Actor_GetReadyFlags(Actor *actor)
{
    u32 result = 0;

    if (actor->mode == 1 && !(actor->flags & 8) && actor->motion == 0 && !(actor->body->dirty & 4)) {
        result |= 1;
    }
    if (actor->gauge->remaining == 0 && (actor->flags & 0x800)) {
        result |= 2;
    }
    return result;
}
