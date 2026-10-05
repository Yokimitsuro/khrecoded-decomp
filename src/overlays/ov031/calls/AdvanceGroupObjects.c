#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    VecFx32 min;
    VecFx32 max;
} Box;

typedef struct {
    VecFx32 *data;
    Box bounds;
    s32 kind;
} CollisionShape;

typedef struct {
    u8 pad_00[0x24];
    CollisionShape shape;
    VecFx32 delta;
    Box box;
    u8 pad_68[0x20];
} GroupObject;

typedef struct {
    u8 hidden;
    u8 slot;
    u8 objectCount;
    u8 pad_03;
    u8 limit;
    u8 counter;
    u8 pad_06[0x2];
    VecFx32 position;
    u8 pad_14[0x4];
    GroupObject *objects;
    u8 pad_1c[0x4];
} ObjectGroup;

typedef struct {
    u8 pad_00[0x64];
    ObjectGroup *groups;
} OverlayState;

extern OverlayState *data_ov031_020bc820;
extern fx32 GetNegatedCombinedOffset(int offset);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void SetShapePosition(CollisionShape *shape, const VecFx32 *position);
extern void OffsetBoxByDelta(const Box *src, Box *dst, const VecFx32 *delta);

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z)
{
    VecFx32 out;
    out.x = x;
    out.y = y;
    out.z = z;
    return out;
}

static inline VecFx32 AddVec(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 out;
    VEC_Add(a, b, &out);
    return out;
}

static inline void MoveShape(CollisionShape *shape, VecFx32 position)
{
    SetShapePosition(shape, &position);
}

BOOL AdvanceGroupObjects(int index)
{
    int i;
    GroupObject *object;
    VecFx32 offset;

    if (data_ov031_020bc820->groups[index].counter < data_ov031_020bc820->groups[index].limit) {
        i = 0;
        offset = MakeVec(0, 0, GetNegatedCombinedOffset(0));
        for (; i < data_ov031_020bc820->groups[index].objectCount; i++) {
            object = &data_ov031_020bc820->groups[index].objects[i];
            data_ov031_020bc820->groups[index].position = AddVec(&data_ov031_020bc820->groups[index].position, &offset);
            MoveShape(&object->shape, AddVec(object->shape.data, &offset));
            OffsetBoxByDelta(&object->shape.bounds, &object->box, &object->delta);
        }
        data_ov031_020bc820->groups[index].hidden = 0;
        if (data_ov031_020bc820->groups[index].counter != 0xff) {
            data_ov031_020bc820->groups[index].counter--;
        }
        return TRUE;
    }
    return FALSE;
}


