#include "nitro/types.h"

typedef struct Vec3i {
    s32 x;
    s32 y;
    s32 z;
} Vec3i;

typedef struct MoveInitInfo {
    s32 *curveValues;
    Vec3i *deltaVector;
    s32 duration;
    u16 kind;
    u16 flags;
    s32 extra;
} MoveInitInfo;

typedef struct SweepSmall {
    s32 w[8];
} SweepSmall;

typedef struct SweepBig {
    s32 w[17];
} SweepBig;

typedef union Sweep {
    SweepSmall small;
    SweepBig big;
} Sweep;

typedef struct MotionState {
    u32 kind;
    u8 pad_04[0x34];
    Sweep sweep;
    u8 hasSweep;
    u8 active;
    u8 pad_7E[2];
    Vec3i deltaVector;
    s32 extra;
    u16 flags;
    u8 pad_92[0x4E];
    s32 duration;
    s32 maxRange;
} MotionState;

typedef struct GlobalMotionQueue {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0c;
    s32 unk_10;
    u8 pad_14[0x18];
    s32 unk_2c;
} GlobalMotionQueue;

extern void func_0203ad28(void *dest, void *target, s32 *values, s32 duration);
extern void OffsetBoxByDelta(s32 *box, s32 *outBox, s32 *shift);
extern GlobalMotionQueue data_027e0134;

void InitMotionState(MotionState *self, MoveInitInfo *info) {
    Vec3i *movement = info->deltaVector;
    u8 hasSweep;

    if (movement->x != 0 || movement->y != 0 || movement->z != 0) {
        SweepBig buf;
        func_0203ad28(&buf, (void *)((u8 *)self + 0x10), info->curveValues, info->duration);
        *(Vec3i *)&buf.w[8] = *movement;
        OffsetBoxByDelta(&buf.w[1], &buf.w[11], &buf.w[8]);
        self->sweep.big = buf;
        hasSweep = 1;
    } else {
        SweepSmall buf;
        func_0203ad28(&buf, (void *)((u8 *)self + 0x10), info->curveValues, info->duration);
        self->sweep.small = buf;
        hasSweep = 0;
    }

    self->hasSweep = hasSweep;
    movement = info->deltaVector;
    self->kind = info->kind;
    self->deltaVector = *movement;
    self->maxRange = 0x7fffffff;
    self->duration = info->duration;
    self->extra = info->extra;
    self->flags = info->flags;
    self->active = 1;

    data_027e0134.unk_04 = 0;
    data_027e0134.unk_08 = 0;
    data_027e0134.unk_0c = 0;
    data_027e0134.unk_10 = 0;
    data_027e0134.unk_2c = 0x7fffffff;
}
