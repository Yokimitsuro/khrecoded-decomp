#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_000[0x194];
    u8 surfaceType;
} GroundSurface;

typedef struct {
    u8 pad_00[0x14];
    GroundSurface *surface;
} GroundObject;

typedef struct {
    u8 pad_00[0x10];
    GroundObject *object;
    u8 pad_14[0xbc - 0x14];
    fx32 height;
    u8 pad_c0[4];
    int valid;
} GroundInfo;

typedef struct {
    VecFx32 position;
    u8 pad_0c[0x0a];
    u16 angle;
    VecFx32 offset;
} ShadowVolume;

typedef struct {
    u8 pad_000[0x274];
    GroundInfo ground;
    u8 pad_33c[0x694 - 0x33c];
    ShadowVolume shadow;
    u8 pad_6b8[0x9ac - 0x6b8];
    u64 stateFlags;
} ShadowActor;

extern int func_ov001_02063a38(void);
extern BOOL func_ov001_020645c8(int id);
extern VecFx32 *func_ov052_020ceb74(ShadowActor *actor);
extern u16 GetLinkedAngleOffset(ShadowActor *actor);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void ShadowVolume_Draw(ShadowVolume *shadow);

void UpdateActorShadow(ShadowActor *actor)
{
    VecFx32 position;
    GroundInfo *ground;
    u8 type;

    if (func_ov001_02063a38() == 4) {
        return;
    }
    if ((actor->stateFlags & 0x200000000ULL) != 0) {
        return;
    }
    position = *func_ov052_020ceb74(actor);
    if (!func_ov001_020645c8(0x3636)) {
        ground = &actor->ground;
        if (ground->valid == 0) {
            return;
        }
        if (ground->object != NULL) {
            type = ground->object->surface->surfaceType;
            if (type != 2 && type != 4) {
                return;
            }
        }
        position.y = ground->height;
        if (func_ov052_020ceb74(actor)->y > position.y + 0x8000) {
            return;
        }
    }
    if (actor->shadow.offset.x != 0 || actor->shadow.offset.y != 0 || actor->shadow.offset.z != 0) {
        VEC_Add(&position, &actor->shadow.offset, &position);
    }
    actor->shadow.position = position;
    actor->shadow.angle = GetLinkedAngleOffset(actor);
    ShadowVolume_Draw(&actor->shadow);
}
