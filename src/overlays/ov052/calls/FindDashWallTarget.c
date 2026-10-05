#include "nitro/types.h"
#include "nitro/fx.h"

typedef struct {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct {
    VecFx32 *data;
    Box bounds;
    s32 kind;
} CollisionShape;

typedef struct {
    CollisionShape shape;
    VecFx32 delta;
    Box sweptBounds;
} SweptShape;

typedef struct {
    u8 data[0x40];
} BoxStorage;

typedef struct {
    u8 data[0x28];
} SegmentStorage;

typedef struct {
    u8 pad_00[0x14];
    s16 normalX;
    s16 normalY;
    s16 normalZ;
    u8 pad_1a[0x50 - 0x1a];
    VecFx32 boundsMin;
    VecFx32 center;
    VecFx32 boundsMax;
    u8 pad_74[0x80 - 0x74];
    u8 meshIndices[4];
} WallSurface;

typedef struct {
    WallSurface *surface;
    int kind;
    int pad_08;
} ContactHit;

typedef struct {
    ContactHit hits[16];
    VecFx32 normals[16];
    u8 count;
    u8 pad_181[0x1a4 - 0x181];
} QueryWorkspace;

typedef struct {
    void (*func)(void);
    void *arg;
} QueryCallback;

typedef struct {
    u32 words[0x14];
    QueryCallback callback;
    u32 tail[2];
} CollisionQuery;

typedef struct {
    u32 words[0x2e];
} CollisionHit;

typedef struct {
    VecFx32 target;
    CollisionHit hit;
    int timer;
    u16 angle;
} DashState;

typedef struct Actor Actor;
typedef int (*StateGetter)(Actor *actor);
typedef VecFx32 *(*OriginGetter)(Actor *actor);

struct Actor {
    u8 pad_0000[0xbc];
    VecFx32 origin;
    u8 pad_00c8[0x1dc - 0xc8];
    int state;
    u8 pad_01e0[0x224 - 0x1e0];
    OriginGetter getOrigin;
    u8 pad_0228[4];
    StateGetter getState;
    void *object;
    u32 bodyFlags;
    u8 pad_0238[0x9b4 - 0x238];
    u8 player;
    u8 pad_09b5[0xa54 - 0x9b5];
    DashState dash;
};

extern s16 data_02053580[];
extern const VecFx32 data_0205344c;
extern void *func_ov001_0206db78(int player);
extern VecFx32 *func_ov052_020ceb74(Actor *actor);
extern BOOL func_ov021_020a7524(void *unit);
extern int func_ov021_020a7564(void *unit);
extern u16 func_ov052_020ceb9c(Actor *actor);
extern void MTX_RotY33_(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void func_ov021_020a9180(VecFx32 *out, const VecFx32 *origin, u16 angle, const VecFx32 *offset);
extern void InitBoxShape(CollisionShape *shape, BoxStorage *storage, const VecFx32 *center, const VecFx32 *halfExtents, const MtxFx33 *rotation);
extern void OffsetBoxByDelta(const Box *src, Box *dst, const VecFx32 *delta);
extern void CollisionQuery_Init(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, void *shape, QueryWorkspace *workspace, void *filter);
extern CollisionHit *SweepWorldCollision(CollisionQuery *query);
extern void func_ov021_020a9494(void);
extern void *GetWorldMeshNamedEntry(int index);
extern BOOL func_ov001_020681e8(void *entry, u32 kind);
extern void func_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern u16 FX_Atan2Idx(fx32 y, fx32 x);
extern void func_01ffa09c(fx32 scale, const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern CollisionShape func_0203ade0(SegmentStorage *storage, const VecFx32 *start, const VecFx32 *end, const VecFx32 *axis, fx32 length);

static inline int GetActorState(Actor *actor)
{
    if (actor->getState != NULL) {
        return actor->getState(actor);
    }
    return actor->state;
}

BOOL FindDashWallTarget(Actor *actor)
{
    CollisionQuery sweep;
    QueryWorkspace workspace;
    SweptShape shapeCopy;
    SweptShape swept;
    CollisionQuery query;
    CollisionQuery dropQuery;
    VecFx32 pos;
    VecFx32 facing;
    SegmentStorage segment;
    CollisionShape segmentShape;
    VecFx32 end;
    VecFx32 start;
    VecFx32 wallPos;
    VecFx32 normal;
    BoxStorage box;
    VecFx32 center;
    VecFx32 halfExtents;
    VecFx32 delta;
    MtxFx33 rotation;
    VecFx32 offset;
    VecFx32 surfaceNormal;
    CollisionShape segmentResult;
    VecFx32 diff;
    VecFx32 axis;
    VecFx32 base;
    QueryCallback callback;
    DashState *dash;
    CollisionHit *hit;
    BOOL found;
    void *unit = func_ov001_0206db78(actor->player);
    u32 ready;
    int angle;

    dash = &actor->dash;
    ready = TRUE;
    if (dash->timer > 0) {
        return FALSE;
    }
    if (GetActorState(actor) == 4 || GetActorState(actor) == 2) {
        return FALSE;
    }
    pos = *func_ov052_020ceb74(actor);
    facing.z = 0;
    facing.y = 0;
    facing.x = 0;
    if (actor->bodyFlags & 4) {
        ready = actor->bodyFlags & 2;
    }
    if (ready && func_ov021_020a7524(unit)) {
        int heading = func_ov021_020a7564(unit);
        facing.x = -data_02053580[heading >> 4];
        facing.z = -data_02053580[(0x400 - (heading >> 4)) & 0xfff];
        angle = (u16)(func_ov052_020ceb9c(actor) - 0x8000);
        MTX_RotY33_(&rotation, -data_02053580[angle >> 4], -data_02053580[(0x400 - (angle >> 4)) & 0xfff]);
        center.x = 0;
        center.y = 0;
        center.z = 0x800;
        func_ov021_020a9180(&center, actor->getOrigin != NULL ? actor->getOrigin(actor) : &actor->origin, angle, &center);
        delta.x = 0;
        delta.y = 0;
        delta.z = 0xb33;
        func_ov021_020a9180(&delta, &data_0205344c, angle, &delta);
        halfExtents.x = 0x900;
        halfExtents.y = 0x666;
        halfExtents.z = 0x333;
        InitBoxShape(&swept.shape, &box, &center, &halfExtents, &rotation);
        swept.delta = delta;
        OffsetBoxByDelta(&swept.shape.bounds, &swept.sweptBounds, &swept.delta);
        shapeCopy = swept;
        CollisionQuery_Init(&query, 0, actor->object, 2, 1, 1, &shapeCopy, &workspace, NULL);
        sweep = query;
        callback.func = func_ov021_020a9494;
        callback.arg = actor->object;
        sweep.callback = callback;
        hit = SweepWorldCollision(&sweep);
        if (hit == NULL) {
            return FALSE;
        }
        found = FALSE;
        {
            int i;
            QueryWorkspace *contacts = &workspace;
            for (i = 0; i < contacts->count; i++) {
                ContactHit *contact = &contacts->hits[i];
                if (contact->kind == 2) {
                    int j;
                    WallSurface *surface = contact->surface;
                    for (j = 0; j < 4; j++) {
                        void *mesh = GetWorldMeshNamedEntry(surface->meshIndices[j]);
                        if (mesh != NULL && func_ov001_020681e8(mesh, 7)) {
                            fx32 top;
                            fx32 maxY;
                            surfaceNormal.x = surface->normalX;
                            surfaceNormal.y = surface->normalY;
                            surfaceNormal.z = surface->normalZ;
                            normal = surfaceNormal;
                            wallPos.x = (surface->boundsMin.x + surface->boundsMax.x) / 2;
                            wallPos.z = (surface->boundsMin.z + surface->boundsMax.z) / 2;
                            maxY = surface->boundsMax.y;
                            top = surface->boundsMin.y;
                            if (top <= maxY) {
                                top = maxY;
                            }
                            wallPos.y = top - 0x1b33;
                            func_01ff9e3c(&pos, &wallPos, &offset);
                            if (VEC_DotProduct(&normal, &offset) > 0x800 && VEC_DotProduct(&facing, &offset) < -0x800) {
                                if (wallPos.y > pos.y) {
                                    wallPos.y = pos.y;
                                }
                                found = TRUE;
                                break;
                            }
                        }
                    }
                }
            }
        }
        if (!found) {
            return FALSE;
        }
        dash->angle = FX_Atan2Idx(normal.x, normal.z);
        normal.y = 0;
        func_01ffa09c(0x59a, &normal, &wallPos, &wallPos);
        dash->hit = *hit;
        base = pos;
        start = base;
        end = base;
        end.y = pos.y + 0xc00;
        start.y = -0x14000;
        func_01ff9e3c(&start, &end, &diff);
        axis = diff;
        segmentResult = func_0203ade0(&segment, &end, &start, &axis, func_01ffaff4(&axis, &axis));
        segmentShape = segmentResult;
        CollisionQuery_Init(&dropQuery, 0, actor->object, 1, 1, 0, &segmentShape, &workspace, NULL);
        sweep = dropQuery;
        if (SweepWorldCollision(&sweep) == NULL) {
            return FALSE;
        }
        {
            fx32 y = segmentShape.data[1].y;
            if (actor->bodyFlags & 4) {
                y += 0x580;
            }
            for (; y < wallPos.y; y += 0x580) {
            }
            wallPos.y = y;
            dash->target = wallPos;
            return TRUE;
        }
    }
    return FALSE;
}
