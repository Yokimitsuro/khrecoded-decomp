#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[4];
    u16 flags;
    u8 pad_06[0x80 - 0x06];
    u16 spin;
    u8 pad_82[0xb4 - 0x82];
    VecFx32 scale;
} FieldActor;

typedef struct {
    u8 pad_00[0x32];
    u8 actorId;
    u8 pad_33[0xc0 - 0x33];
    u32 flags;
    u8 pad_c4[0xcc - 0xc4];
    s32 timer;
    u8 pad_d0[4];
    s32 spin;
    u32 effectId : 8;
    u32 effectRest : 24;
} FieldObject;

extern const VecFx32 data_ov016_020a6e18;
extern FieldActor *ActorRegistry_GetEntityByIndex(u32 actorId);
extern void InitializeFieldEffect(FieldObject *obj, u8 effectId);

void AnimateLaunchedFieldObject(FieldObject *obj)
{
    FieldActor *actor;
    VecFx32 scale;
    int value;
    int timer;
    int half;

    if (obj->timer > 0) {
        obj->timer -= 0x89;
        if (obj->timer < 0) {
            InitializeFieldEffect(obj, obj->effectId);
        }
    }
    if (obj->flags & 0x40000) {
        actor = ActorRegistry_GetEntityByIndex(obj->actorId);
        scale = data_ov016_020a6e18;
        value = 0;
        timer = obj->timer;
        if (timer != 0) {
            value = 0x3000 % timer;
            half = timer / 2;
            if (half != 0) {
                if (value >= half) {
                    value -= half;
                    value = (half - value) * 0x19a / half;
                } else {
                    value = value * 0x19a / half;
                }
            } else {
                value = 0;
            }
            scale.x = scale.z = value + 0x1000;
            value = obj->spin * 7 / 10;
        }
        obj->spin = value;
        actor->spin = value;
        actor->flags |= 0x20;
        actor->scale = scale;
    }
}
