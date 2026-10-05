#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    fx32 x;
    fx32 y;
    fx32 z;
    fx32 w;
} QuatFx32;

typedef struct {
    u8 pad_00[0x3c];
    s32 active;
} SpinSlot;

typedef struct {
    s32 phase : 16;
    s32 mode : 16;
} SpinState;

typedef struct {
    SpinSlot slots[8];
    QuatFx32 spin;
    fx32 facing;
    fx32 step;
    fx32 timer;
    fx32 timer2;
    u8 pad_220[0x22c - 0x220];
    SpinState state;
} SpinParams;

typedef struct {
    u8 pad_00[0xc];
    fx32 hitRadius;
    u8 pad_10[0x1c - 0x10];
    fx32 hitDuration;
    u8 pad_20[0x24 - 0x20];
    fx32 windupDuration;
} SpinDef;

typedef struct {
    u8 pad_000[2];
    s8 status;
    u8 pad_003;
    fx32 age;
    u8 pad_008[0xd4 - 0x8];
    VecFx32 position;
    u8 pad_0e0[0x138 - 0xe0];
    SpinDef *def;
    u8 pad_13c[0x150 - 0x13c];
    SpinParams *params;
} SpinUnit;

typedef struct {
    u8 pad_000[0x18c];
    fx32 spinSpeed;
} SpinOwner;

extern const VecFx32 data_ov056_020d7f90;

extern int FX_Mul(int left, int right);
extern void QuatFromAxisAngle(QuatFx32 *out, const VecFx32 *axis, fx32 angle);
extern void func_ov021_020ab310(SpinUnit *unit, int blend);
extern int func_ov021_020ab43c(SpinUnit *unit, fx32 step);
extern void func_ov056_020d5328(VecFx32 *center, fx32 radius, SpinOwner *owner, void *extra);

BOOL UpdateSpinAttackUnit(SpinOwner *owner, SpinUnit *unit, fx32 step)
{
    SpinDef *def = unit->def;
    SpinParams *params = unit->params;
    fx32 angle;
    int i;

    unit->age += step;
    angle = FX_Mul(owner->spinSpeed, step);
    QuatFromAxisAngle(&params->spin, &data_ov056_020d7f90, angle);
    params->facing = (fx32)(((s64)angle * 0x394BB834C8LL + 0x80000000LL) >> 32);
    params->step = step;

    switch (params->state.mode) {
    default:
        params->state.mode = 0;
        break;
    case 0:
    case 2:
        break;
    case 1:
        params->state.phase = 1;
        params->state.mode = 2;
        break;
    case 3:
        if (params->state.phase == 0) {
            params->state.mode = 4;
        }
        break;
    case 4:
        func_ov021_020ab310(unit, 2);
        params->state.mode = 5;
    case 5:
        params->state.mode = 0;
        break;
    }

    switch (params->state.phase) {
    case 0:
        break;
    case 1:
        for (i = 0; i < 8; i++) {
            params->slots[i].active = 0;
        }
        params->timer = 0;
        params->timer2 = 0;
        params->state.phase = 2;
    case 2:
        if (params->timer < def->windupDuration) {
            params->timer += step;
        } else {
            params->timer = 0;
            params->state.phase = 3;
        }
        break;
    case 3:
        if (params->timer < def->hitDuration) {
            func_ov056_020d5328(&unit->position, def->hitRadius, owner, unit);
            params->timer += step;
        } else {
            params->state.phase = 0;
            for (i = 0; i < 8; i++) {
                params->slots[i].active = 0;
            }
        }
        break;
    }

    if (unit->status == 1 && (u16)func_ov021_020ab43c(unit, step) != 0) {
        switch (params->state.mode) {
        case 0:
            unit->status = -1;
            break;
        case 2:
            func_ov021_020ab310(unit, 1);
            params->state.mode = 3;
            break;
        }
    }
    if (unit->status == -1) {
        return TRUE;
    }
    return FALSE;
}
