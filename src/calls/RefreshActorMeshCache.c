#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct VecS16 {
    s16 x;
    s16 y;
    s16 z;
} VecS16;

typedef struct CollBox {
    VecFx32 max;
    VecFx32 min;
} CollBox;

typedef struct CollShape {
    void *geometry;
    CollBox box;
    s32 kind;
} CollShape;

typedef struct CollSweep {
    CollShape shape;
    VecFx32 delta;
    CollBox sweptBox;
} CollSweep;

typedef struct CollActor {
    u8 pad_000[0x3c];
    u8 cacheStamp;
    u8 pad_03D[0x287];
    CollBox cacheBox;
    u8 pad_2DC[0x180];
    VecS16 groundNormal;
} CollActor;

typedef struct CollQuery {
    u8 pad_00[0x24];
    union {
        u16 maxHits;
        u32 word;
    } limit;
    union {
        s16 *ptr;
        u32 word;
    } outX;
    s16 *outY;
    union {
        s16 *outZ;
        s32 normalX;
    } result;
    s32 normalY;
    s32 normalZ;
    u8 flag3C;
    u8 flag3D;
} CollQuery;

extern u8 data_02060780;
extern void func_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void TestQueryAgainstMeshList(void *list, void *params);

static inline BOOL IsBoxInside(const CollBox *box, const CollBox *cache)
{
    return box->max.x <= cache->max.x && box->min.x >= cache->min.x &&
           box->max.y <= cache->max.y && box->min.y >= cache->min.y &&
           box->max.z <= cache->max.z && box->min.z >= cache->min.z;
}

static inline fx32 AbsFx32(fx32 value)
{
    return value < 0 ? -value : value;
}

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z)
{
    VecFx32 vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    return vec;
}

static inline VecFx32 AddVec(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 sum;
    func_01ff9e0c(a, b, &sum);
    return sum;
}

static inline VecFx32 SubVec(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 diff;
    func_01ff9e3c(a, b, &diff);
    return diff;
}

void RefreshActorMeshCache(void *world, CollActor *actor, CollQuery *query, CollSweep *sweep, const VecFx32 *velocity)
{
    BOOL refresh;

    if (actor->cacheStamp != data_02060780) {
        actor->cacheStamp = data_02060780;
        refresh = TRUE;
    } else {
        CollBox box = sweep->sweptBox;
        box.min.y -= 0x50000;
        refresh = !IsBoxInside(&box, &actor->cacheBox);
    }
    if (refresh) {
        u32 savedLimit = query->limit.word;
        u32 savedOut = query->outX.word;
        u8 savedFlag3C = query->flag3C;
        u8 savedFlag3D = query->flag3D;
        VecFx32 margin = MakeVec(AbsFx32(velocity->x) + 0x2000, AbsFx32(velocity->y) + 0x2000, AbsFx32(velocity->z) + 0x2000);

        actor->cacheBox.max = AddVec(&sweep->shape.box.max, &margin);
        actor->cacheBox.min = SubVec(&sweep->shape.box.min, &margin);
        actor->cacheBox.min.y -= 0x50000;
        query->limit.maxHits = 0x20;
        query->outX.ptr = &actor->groundNormal.x;
        query->outY = &actor->groundNormal.y;
        query->result.outZ = &actor->groundNormal.z;
        TestQueryAgainstMeshList(world, query);
        query->limit.word = savedLimit;
        query->outX.word = savedOut;
        query->flag3C = savedFlag3C;
        query->flag3D = savedFlag3D;
    }
    query->result.normalX = actor->groundNormal.x;
    query->normalY = actor->groundNormal.y;
    query->normalZ = actor->groundNormal.z;
}
