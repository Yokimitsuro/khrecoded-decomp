#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionShape {
    void *data;
    VecFx32 boundsMin;
    VecFx32 boundsMax;
    s32 kind;
} CollisionShape;

typedef struct ShapeTemplate {
    CollisionShape shape;
    VecFx32 offset;
} ShapeTemplate;

typedef struct { u32 words[4]; } SphereData;
typedef struct { u32 words[16]; } BoxData;
typedef struct { u32 words[10]; } CapsuleData;
typedef struct { u32 words[11]; } CylinderData;
typedef struct { u32 words[52]; } PolygonData;

extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void SetShapePosition(CollisionShape *shape, const VecFx32 *position);

static inline VecFx32 AddVec(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 out;
    VEC_Add(a, b, &out);
    return out;
}

static inline void MoveShapeTo(CollisionShape *shape, VecFx32 position)
{
    SetShapePosition(shape, &position);
}

void CopyShapeFromTemplate(const ShapeTemplate *source, CollisionShape *shape, void *buffer)
{
    *shape = source->shape;
    shape->data = buffer;
    switch (source->shape.kind) {
    case 0:
        *(SphereData *)buffer = *(SphereData *)source->shape.data;
        break;
    case 1:
        *(BoxData *)buffer = *(BoxData *)source->shape.data;
        break;
    case 2:
        *(CapsuleData *)buffer = *(CapsuleData *)source->shape.data;
        break;
    case 3:
        *(CylinderData *)buffer = *(CylinderData *)source->shape.data;
        break;
    case 4:
        *(CylinderData *)buffer = *(CylinderData *)source->shape.data;
        break;
    case 5:
        *(PolygonData *)buffer = *(PolygonData *)source->shape.data;
        break;
    }
    MoveShapeTo(shape, AddVec((VecFx32 *)shape->data, &source->offset));
}
