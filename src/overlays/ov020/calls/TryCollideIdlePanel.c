#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Collider {
    u8 pad_00[0x1c];
    int shapeType;
    VecFx32 velocity;
    VecFx32 max;
    VecFx32 min;
} Collider;

typedef struct Shape {
    u8 pad_00[4];
    VecFx32 max;
    VecFx32 min;
    int shapeType;
} Shape;

typedef struct Panel {
    u8 pad_00[0x10];
    Shape shape;
    u8 pad_30[0x18];
    s8 state;
} Panel;

typedef int (*CollideFunc)(Shape *shape, Collider *other, void *result, int flags);
typedef int (*CollideMovingFunc)(Shape *shape, Collider *other, void *result, int flags, VecFx32 *push);

extern CollideFunc gCollisionTestPairDispatch[][6];
extern CollideMovingFunc gCollisionSweepPairDispatch[][6];
extern void NegateVecFx32(VecFx32 *vec);

int TryCollideIdlePanel(Panel *panel, Collider *other, void *result)
{
    VecFx32 reversed;
    VecFx32 push;
    int overlap;

    if (panel->shape.shapeType >= 0 && panel->state == 0) {
        if (panel->shape.max.x >= other->min.x && panel->shape.min.x <= other->max.x &&
            panel->shape.max.z >= other->min.z && panel->shape.min.z <= other->max.z &&
            panel->shape.max.y >= other->min.y && panel->shape.min.y <= other->max.y) {
            if (other->velocity.x == 0 && other->velocity.y == 0 && other->velocity.z == 0) {
                overlap = 2;
            } else {
                reversed = other->velocity;
                NegateVecFx32(&reversed);
                push = reversed;
                overlap = 1;
            }
        } else {
            overlap = 0;
        }
        if (overlap != 0) {
            if (overlap == 2) {
                return gCollisionTestPairDispatch[panel->shape.shapeType][other->shapeType](&panel->shape, other, result, (other->shapeType == 2 ? 2 : 0) | 8);
            }
            return gCollisionSweepPairDispatch[panel->shape.shapeType][other->shapeType](&panel->shape, other, result, 8, &push);
        }
        return 0;
    }
    return 0;
}
