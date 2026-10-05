#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    VecFx32 *points;
    s8 pointCount;
    u8 pad_05[3];
} PatrolRoute;

typedef struct PatrolObject PatrolObject;

struct PatrolObject {
    u8 pad_00[0x14];
    void (*update)(PatrolObject *object);
    u8 pad_18[0x40 - 0x18];
    VecFx32 position;
    u8 pad_4c[0x58 - 0x4c];
    s32 timer;
    s32 counter;
    PatrolRoute *routes;
    VecFx32 direction;
    u8 pad_70[0x7d - 0x70];
    s8 routeIndex;
    u8 pad_7e;
    s8 pointIndex;
    s8 startIndex;
    s8 state;
    u8 pad_82[2];
    u8 resource[1];
};

typedef struct {
    u8 pad_000[0x214];
    u32 flags;
} FieldState;

extern FieldState *data_ov001_020a0480;

extern void FieldObject_AdvanceRandomVariant(PatrolObject *object);
extern void UpdatePatrolIdle(PatrolObject *object);
extern u32 random_next_scaled(int range);
extern signed char func_ov001_02068084(void);
extern void ReleaseResourceAndDetach(void *resource);
extern void ReleaseOwnerResource(PatrolObject *object, void *owner);

void ResetPatrolObject(PatrolObject *object, void *owner) {
    VecFx32 direction;
    int index;

    if (object->state == 3) {
        FieldObject_AdvanceRandomVariant(object);
    }
    object->update = UpdatePatrolIdle;
    object->timer = 0;
    object->counter = 0;
    object->state = 0;
    object->pointIndex = random_next_scaled(object->routes[object->routeIndex].pointCount);
    index = object->pointIndex;
    object->startIndex = index;
    object->position = object->routes[object->routeIndex].points[index];
    direction.x = 0;
    direction.y = 0;
    direction.z = FX32_ONE;
    object->direction = direction;
    if (func_ov001_02068084() != 7) {
        ReleaseResourceAndDetach(object->resource);
    }
    data_ov001_020a0480->flags &= ~0x80000;
    ReleaseOwnerResource(object, owner);
}
