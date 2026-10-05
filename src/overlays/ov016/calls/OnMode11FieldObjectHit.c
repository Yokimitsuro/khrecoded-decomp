#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 locked;
    u8 variant;
} HitState;

typedef struct {
    u8 pad_000[0x194];
    HitState state;
} HitOwner;

typedef struct {
    HitOwner **owner;
    int kind;
} HitSource;

typedef struct {
    HitSource *source;
    int type;
} HitInfo;

typedef struct {
    u8 pad_00[0x77];
    u8 mode;
    u8 pad_78[0xc0 - 0x78];
    u32 flags;
    u8 pad_c4[0xcc - 0xc4];
    fx32 speed;
    u8 pad_d0[4];
    fx32 lift;
    u32 variant : 8;
    u32 variantRest : 24;
} FieldObject;

typedef struct {
    FieldObject *obj;
    int arg1;
    int arg2;
    int arg3;
} HitContext;

extern void func_ov016_020a568c(void *self, void *other, void *contact, HitInfo *hit, FieldObject *obj, int arg1, int arg2, int arg3);

void OnMode11FieldObjectHit(void *self, void *other, void *contact, HitInfo *hit, HitContext context)
{
    FieldObject *obj = context.obj;
    HitState *state;

    if (obj->mode == 11 && !(obj->flags & 0x40000) && hit != NULL && hit->type == 2 &&
        hit->source->kind == 0) {
        state = &(*hit->source->owner)->state;
        if (state->locked == 0 && state->variant == 0) {
            obj->flags |= 0x40000;
            obj->speed = 0x3000;
            obj->lift = 0x80000;
            obj->variant = state->variant;
        }
    }
    func_ov016_020a568c(self, other, contact, hit, context.obj, context.arg1, context.arg2, context.arg3);
}
