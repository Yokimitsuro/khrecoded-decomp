#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct {
    u32 _0;
    Box src;
    u32 _1c;
    VecFx32 delta;
    Box dst;
    u8 _44[0x44];
} CameraCollider;

typedef struct {
    u8 _0[0x11c];
    VecFx32 offset;
    u8 _128[0x308];
    CameraCollider colliders[3];
} CameraState;

extern CameraState *data_ov042_020be5e0;
extern void OffsetBoxByDelta(const Box *src, Box *dst, const VecFx32 *delta);

static inline void OffsetCollider(CameraCollider *collider, const VecFx32 *delta) {
    collider->delta = *delta;
    OffsetBoxByDelta(&collider->src, &collider->dst, &collider->delta);
}

void OffsetCameraColliders(const VecFx32 *delta) {
    data_ov042_020be5e0->offset = *delta;
    OffsetCollider(&data_ov042_020be5e0->colliders[0], delta);
    OffsetCollider(&data_ov042_020be5e0->colliders[1], delta);
    OffsetCollider(&data_ov042_020be5e0->colliders[2], delta);
}
