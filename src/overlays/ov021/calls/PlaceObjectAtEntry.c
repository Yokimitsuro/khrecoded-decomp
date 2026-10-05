#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    u8 pad_00;
    s8 entryIndex;
    u8 pad_02[2];
    u16 mode;
    u8 pad_06[2];
    u16 flags;
    u8 pad_0a[0x7a];
    u16 yaw;
    u16 pitch;
    u8 pad_88[0x24];
    VecFx32 position;
    u8 pad_b8[0x64];
    VecFx32 offset;
    u16 yawOffset;
} PlacedObject;

extern const s16 data_02053580[];
extern u16 GetBiasAdjustedField(int index);
extern VecFx32 *func_ov001_0206dc60(int index);
extern VecFx32 *func_ov001_0206dc4c(int index);
extern void MTX_RotY33_(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_MultVec33(const VecFx32 *vec, const MtxFx33 *mtx, VecFx32 *dst);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void func_ov021_020a87a4(PlacedObject *object, int yaw, int pitch);

static inline void SetYaw(PlacedObject *object, u16 yaw) {
    object->yaw = yaw;
    object->flags |= 0x20;
}

static inline void SetPitch(PlacedObject *object, u16 pitch) {
    object->pitch = pitch;
    object->flags |= 0x20;
}

void PlaceObjectAtEntry(PlacedObject *object) {
    u16 angle = GetBiasAdjustedField(object->entryIndex);
    VecFx32 *base;
    MtxFx33 rot;
    VecFx32 pos;
    int index;
    if (object->mode & 1) {
        base = func_ov001_0206dc60(object->entryIndex);
    } else {
        base = func_ov001_0206dc4c(object->entryIndex);
    }
    index = angle >> 4;
    MTX_RotY33_(&rot, -data_02053580[index], -data_02053580[(0x400 - index) & 0xfff]);
    MTX_MultVec33(&object->offset, &rot, &pos);
    VEC_Add(base, &pos, &pos);
    object->position = pos;
    SetPitch(object, 0);
    if (object->mode & 0x10) {
        SetYaw(object, angle);
        SetPitch(object, object->yawOffset);
    } else if (object->mode & 8) {
        func_ov021_020a87a4(object, angle, object->yawOffset);
    } else {
        SetYaw(object, angle + object->yawOffset);
    }
}
