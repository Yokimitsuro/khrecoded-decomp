#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct {
    VecFx32 position;
} Shape;

typedef struct {
    u8 pad_000[0xa8];
    VecFx32 position;
    u8 pad_0b4[0x65];
    u8 falling;
    u8 pad_11a[0x16];
    Shape *shape;
    Box box;
    u8 pad_14c[4];
    VecFx32 delta;
    Box sweptBox;
} Actor;

typedef struct {
    u8 pad_00[0x38];
    u8 actorId;
    u8 pad_39[7];
    VecFx32 position;
    u8 pad_4c[0x10];
    fx32 velocity;
} FieldObject;

typedef struct {
    void *hit;
    s32 hitType;
    u8 pad_08[0x19c];
} QueryWorkspace;

typedef struct {
    void *func;
    void *context;
} QueryCallback;

typedef struct {
    s32 unk_00;
    s32 mask;
} QueryFilter;

typedef struct {
    u8 pad_00[0x48];
    QueryCallback filter;
    QueryCallback check;
    u8 pad_58[8];
} CollisionQuery;

extern const VecFx32 data_0205344c;

extern Actor *ActorRegistry_GetEntityByIndex(u32 id);
extern void OffsetBoxByDelta(const Box *src, Box *dst, const VecFx32 *delta);
extern void CollisionQuery_Init(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, void *shape, QueryWorkspace *workspace, QueryFilter *filter);
extern BOOL SweepWorldCollision(CollisionQuery *query);
extern BOOL IsKind4WithState0Or3();

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z)
{
    VecFx32 vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    return vec;
}

static inline QueryFilter MakeFilter(s32 value, s32 mask)
{
    QueryFilter filter;
    filter.unk_00 = value;
    filter.mask = mask;
    return filter;
}

static inline QueryCallback MakeCallback(void *func, void *context)
{
    QueryCallback callback;
    callback.func = func;
    callback.context = context;
    return callback;
}

void FieldObject_UpdateFall(FieldObject *object)
{
    Actor *actor;
    CollisionQuery sweep;
    QueryWorkspace workspace;
    CollisionQuery query;
    QueryFilter filter;

    filter = MakeFilter(0, 0x1f);
    actor = ActorRegistry_GetEntityByIndex(object->actorId);
    object->velocity -= 0xcd;
    actor->falling = 1;
    actor->delta = MakeVec(0, object->velocity, 0);
    OffsetBoxByDelta(&actor->box, &actor->sweptBox, &actor->delta);
    CollisionQuery_Init(&query, 0, actor, 9, 1, 1, &actor->shape, &workspace, &filter);
    sweep = query;
    sweep.filter = MakeCallback(IsKind4WithState0Or3, object);
    if (SweepWorldCollision(&sweep)) {
        object->velocity = 0;
        actor->delta = data_0205344c;
        OffsetBoxByDelta(&actor->box, &actor->sweptBox, &actor->delta);
    }
    object->position = actor->shape->position;
    object->position.y -= 0x800;
    actor->position = object->position;
}
