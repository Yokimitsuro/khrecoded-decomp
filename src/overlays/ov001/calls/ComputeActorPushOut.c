#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Surface {
    u8 pad_00[0x24];
    VecFx32 *position;
    u8 pad_28[0x8c - 0x28];
    fx32 height;
} Surface;

typedef struct PushActor {
    u8 pad_000[0x11c];
    Surface surface;
    u8 pad_1ac[0x2bc - 0x1ac];
    fx32 height;
    u8 pad_2c0[0x31c - 0x2c0];
    fx32 scale;
    u8 pad_320[0x398 - 0x320];
    fx32 weight;
} PushActor;

typedef struct PushEvent {
    u8 pad_00[0x61];
    u8 allowLift;
} PushEvent;

extern const VecFx32 data_0205344c;
extern fx32 Surface_GetKindValue(Surface *surface);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void RandomHorizontalVector(int seed, VecFx32 *out);
extern fx32 VEC_Mag(const VecFx32 *v);
extern BOOL func_ov001_02063a24(void);
extern int func_ov001_02063a38(void);
extern fx32 FX_Div(fx32 numer, fx32 denom);
extern void func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);

#define FX_MUL(a, b) ((fx32)(((fx64)(a) * (b) + 0x800) >> 12))

static inline int GetSessionMode(void)
{
    if (!func_ov001_02063a24()) {
        return 0;
    }
    return func_ov001_02063a38();
}

BOOL ComputeActorPushOut(PushEvent *event, PushActor *actor, Surface *other, VecFx32 *position, const VecFx32 *target, fx32 margin, VecFx32 *outSelf, VecFx32 *outOther)
{
    fx32 radius;
    Surface *surface;
    fx32 height;
    fx32 climb;
    fx32 distance;
    fx32 reach;
    fx32 ratio;
    fx32 push;
    fx32 selfScale;
    fx32 otherScale;
    VecFx32 direction;
    VecFx32 delta;

    surface = &actor->surface;
    if (other != NULL) {
        surface = other;
    }
    radius = Surface_GetKindValue(surface);
    if (other != NULL) {
        radius = FX_MUL(radius, actor->scale);
        height = FX_MUL(other->height, actor->scale);
    } else {
        height = FX_MUL(actor->height, actor->scale);
    }
    climb = height - radius;
    if (climb <= 0) {
        climb = 0;
    }
    if (position == NULL) {
        position = surface->position;
    }
    if (climb != 0) {
        fx32 diff;
        fx32 lifted;
        fx32 gap;

        lifted = position->y + climb;
        diff = target->y - lifted;
        gap = diff < 0 ? -diff : diff;

        if (gap > climb + radius) {
            return FALSE;
        }
        if (diff >= climb) {
            diff = climb;
        }
        if (diff <= -climb) {
            diff = -climb;
        }
        position->y = lifted + diff;
    }
    VEC_Subtract(position, target, &delta);
    if ((delta.x < 0 ? -delta.x : delta.x) < 0x80 && (delta.z < 0 ? -delta.z : delta.z) < 0x80) {
        fx32 savedY = delta.y;
        RandomHorizontalVector(0x29, &delta);
        delta.y = savedY;
    }
    distance = VEC_Mag(&delta);
    reach = radius + margin + 0x19a;
    if (distance >= reach) {
        return FALSE;
    }
    if (GetSessionMode() == 4) {
        ratio = 0x800;
    } else if (actor->weight == 0x7fffffff) {
        ratio = 0x1000;
    } else {
        ratio = FX_Div(actor->weight, actor->weight + 0x1000);
    }
    if (!event->allowLift && delta.y > 0) {
        delta.y = 0;
    }
    push = FX_MUL(reach - distance, 0xccd);
    selfScale = FX_MUL(push, 0x1000 - ratio);
    otherScale = FX_MUL(push, ratio);
    func_01ffaff4(&delta, &direction);
    if (GetSessionMode() == 4) {
        direction.y = 0;
    }
    VEC_MultAdd(selfScale, &direction, &data_0205344c, outSelf);
    VEC_MultAdd(-otherScale, &direction, &data_0205344c, outOther);
    return TRUE;
}

