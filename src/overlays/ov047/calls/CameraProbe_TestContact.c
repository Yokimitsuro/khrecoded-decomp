#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ProbeShape {
    u8 pad_00[0x4];
    VecFx32 max;
    VecFx32 min;
    int kind;
} ProbeShape;

typedef struct CollisionOwner {
    u8 pad_00[0x24];
    ProbeShape shape;
    u8 pad_44[0x28];
    int objectType;
} CollisionOwner;

typedef struct ContactRef {
    CollisionOwner *owner;
    int category;
} ContactRef;

typedef struct ContactQuery {
    u8 pad_00[0x4];
    VecFx32 direction;
    fx32 speed;
} ContactQuery;

typedef struct CameraProbe {
    BOOL hit;
    BOOL decelerate;
    u8 pad_08[0x10];
    ProbeShape shape;
} CameraProbe;

typedef struct ProbeSource {
    VecFx32 *base;
    u8 pad_04[0x1c];
    VecFx32 offset;
} ProbeSource;

typedef BOOL (*ShapeTestFn)(ProbeShape *self, ProbeShape *other, void *hit, int flags);

extern ShapeTestFn gCollisionTestPairDispatch[][6];
extern BOOL IsFacingContactNormal(ContactRef *ref, const VecFx32 *direction);
extern s8 func_ov001_02068084(void);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void SetShapePosition(ProbeShape *shape, const VecFx32 *position);

BOOL CameraProbe_TestContact(ContactRef *ref, ContactQuery *query, CameraProbe *probe, ProbeSource *source)
{
    if (!IsFacingContactNormal(ref, &query->direction)) {
        return FALSE;
    }
    if (ref->category == 4 && func_ov001_02068084() != 5) {
        int type = ref->owner->objectType;
        if (type == 0x1e || type == 1 || type == 0x23) {
            VecFx32 position;
            VecFx32 sum;
            ProbeShape *other;
            BOOL result;

            VEC_Add(source->base, &source->offset, &sum);
            position = sum;
            SetShapePosition(&probe->shape, &position);
            other = &ref->owner->shape;
            if (probe->shape.max.x >= other->min.x && probe->shape.min.x <= other->max.x &&
                probe->shape.max.z >= other->min.z && probe->shape.min.z <= other->max.z &&
                probe->shape.max.y >= other->min.y && probe->shape.min.y <= other->max.y) {
                result = gCollisionTestPairDispatch[probe->shape.kind][other->kind](&probe->shape, other, NULL, 0);
            } else {
                result = FALSE;
            }
            if (!result) {
                return FALSE;
            }
            probe->hit = TRUE;
        }
    }
    if (probe->decelerate) {
        query->speed -= 0x80000;
        if (query->speed < 0) {
            query->speed = 0;
        }
    }
    return TRUE;
}

