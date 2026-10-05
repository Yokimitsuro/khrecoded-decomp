#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s32 type;
    VecFx32 direction;
    VecFx32 origin;
    s32 arg;
    u8 pad_20[4];
    u32 flags;
    u8 pad_28[0xc];
    s32 result;
} PushMessage;

typedef struct {
    u16 pad_00;
    u16 enabled;
} EntityTraits;

typedef struct PushEntity PushEntity;
struct PushEntity {
    u8 pad_000[0xbc];
    VecFx32 position;
    u8 pad_0c8[0x10c];
    EntityTraits *traits;
    u8 pad_1d8[0x30];
    BOOL (*onMessage)(PushEntity *entity, PushMessage *message);
};

typedef struct {
    u8 pad_00[0x38];
    VecFx32 position;
} PushSource;

extern PushEntity *GetBoundedEntryField(int index);
extern void *GetEntryFieldForMode(int index);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern u32 random_next_scaled(u32 range);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern void ScaleVecFx32InPlace(VecFx32 *v, fx32 scale);
extern void MI_CpuFill8(void *dst, int value, u32 size);

static inline VecFx32 ScaledVec(const VecFx32 *v, fx32 scale)
{
    VecFx32 result = *v;
    ScaleVecFx32InPlace(&result, scale);
    return result;
}

BOOL SendPushMessage(PushSource *source, int index, int unused, s32 arg)
{
    PushEntity *entity = GetBoundedEntryField(index);
    PushMessage message;
    VecFx32 push;
    VecFx32 offset;
    VecFx32 unit;
    BOOL handled;

    if (entity->traits->enabled != 0) {
        GetEntryFieldForMode(index);
        VEC_Subtract(&entity->position, &source->position, &offset);
        offset.y = 0;
        if (offset.x == 0 && offset.y == 0 && offset.z == 0) {
            offset.x = random_next_scaled(0x1000) - 0x800;
            if (offset.x == 0 && offset.y == 0 && offset.z == 0) {
                offset.x = 0x1000;
            }
        }
        VEC_Normalize(&offset, &unit);
        push = ScaledVec(&unit, 0x800);
        handled = FALSE;
        MI_CpuFill8(&message, 0, sizeof(message));
        message.type = 0x4c;
        message.arg = arg;
        message.direction = push;
        message.origin = source->position;
        message.result = 0;
        if (entity->onMessage != 0) {
            handled = entity->onMessage(entity, &message);
        }
        if (handled && !(message.flags & 1)) {
            return TRUE;
        }
    }
    return FALSE;
}

