#include "nitro/types.h"

typedef struct {
    u8 kind;
    u8 group;
    u8 index;
} HitState;

typedef struct {
    u8 pad_000[0x194];
    HitState state;
} HitOwner;

typedef struct {
    u8 pad_00[0x14];
    HitOwner *owner;
} HitSource;

typedef struct {
    HitSource *source;
    int type;
} HitInfo;

typedef struct {
    u8 pad_00[4];
    int strength;
} HitResult;

typedef struct {
    u8 pad_00[0x47];
    s8 carryState;
    u8 pad_48[0x77 - 0x48];
    u8 mode;
    u8 pad_78[0xbe - 0x78];
    u8 unk_BE_low : 4;
    u8 state : 4;
    u8 pad_bf[0xe8 - 0xbf];
    u16 hitGroup;
    u16 hitIndex;
} FieldObject;

extern FieldObject *func_ov001_0208724c(u32 group, u32 index);
extern void PairFieldObjects(FieldObject *first, FieldObject *second);

void OnFieldObjectBumped(HitInfo *hit, HitResult *result, FieldObject *obj)
{
    FieldObject *other;
    HitState *state;

    if (hit->type != 4) {
        return;
    }
    state = &hit->source->owner->state;
    if (state->kind != 4) {
        return;
    }
    other = func_ov001_0208724c(state->group, state->index);
    if (obj->state == 0 &&
        ((obj->mode == 12 && other->mode == 13) || (obj->mode == 13 && other->mode == 12) ||
         (obj->mode == 14 && other->mode == 15) || (obj->mode == 15 && other->mode == 14)) &&
        obj->state == other->state && obj->carryState != 2 && other->carryState != 2) {
        PairFieldObjects(obj, other);
    }
    if (result->strength > 0) {
        obj->hitGroup = state->group;
        obj->hitIndex = state->index;
    }
}
