#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct CollisionShape {
    void *data;
    s32 bounds[6];
    s32 kind;
} CollisionShape;

typedef struct BoxStorage {
    u8 data[0x40];
} BoxStorage;

typedef struct QueryWorkspace {
    u8 pad_000[0x1a4];
} QueryWorkspace;

typedef struct QueryCallback {
    void (*func)(void);
    void *arg;
} QueryCallback;

typedef struct CollisionQuery {
    u32 words[0x12];
    QueryCallback filter;
    QueryCallback callback;
    u32 tail[2];
} CollisionQuery;

typedef struct QuadTreeRef {
    void *root;
} QuadTreeRef;

typedef struct World {
    u32 pad_00;
    QuadTreeRef *tree;
} World;

typedef struct Actor {
    u32 flags;
    u8 pad_04[0xb4 - 0x4];
    VecFx32 scale;
    u8 pad_c0[0x10c - 0xc0];
    u8 node[4];
} Actor;

typedef struct FieldObject {
    u8 pad_00[0x32];
    u8 actorId;
    u8 pad_33[0x38 - 0x33];
    VecFx32 position;
    u8 pad_44[0x3];
    s8 pressed;
    u8 pad_48[0xc0 - 0x48];
    u32 flags;
    u8 pad_c4[0xcc - 0xc4];
    fx32 timer;
    fx32 pressTime;
    fx32 releaseTime;
    fx32 holdTime;
} FieldObject;

extern const VecFx32 data_ov016_020a6e0c;
extern const MtxFx33 data_02053458;
extern Actor *ActorRegistry_GetEntityByIndex(int actorId);
extern World *GetActorRegistry(void);
extern void InitBoxShape(CollisionShape *shape, void *storage, const VecFx32 *center, const VecFx32 *halfExtents, const MtxFx33 *rotation);
extern void CollisionQuery_Init(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, void *shape, QueryWorkspace *workspace, void *filter);
extern void *SweepWorldCollision(CollisionQuery *query);
extern void func_ov016_020a41e0(void);
extern void func_ov001_0208645c(FieldObject *object, int mode);
extern void QuadTree_InsertObject(void *tree, void *node);
extern void QuadTree_RemoveObject(void *tree, void *node);
extern void func_ov016_020a229c(FieldObject *object, BOOL enable);

void UpdateFloorSwitch(FieldObject *object)
{
    BOOL done = FALSE;
    int pressed = object->pressed;
    fx32 scale;
    BOOL enable;

    if (!(object->flags & 0x4000)) {
        object->timer += 0x89;
        if (object->pressTime <= object->timer) {
            done = TRUE;
            object->flags |= 0x4000;
            object->flags &= ~0x1000;
        } else {
            object->flags |= 0x1000;
        }
    } else {
        object->timer += 0x89;
        if (object->flags & 0x1000) {
            if (object->holdTime <= object->timer) {
                object->flags &= ~0x1000;
                done = TRUE;
            }
        } else {
            if (object->releaseTime <= object->timer) {
                object->flags |= 0x1000;
                done = TRUE;
            }
        }
    }
    if (pressed == 1) {
        QueryWorkspace workspace;
        CollisionQuery query;
        VecFx32 extent = data_ov016_020a6e0c;
        VecFx32 center;
        CollisionShape shape;
        BoxStorage storage;
        Actor *actor = ActorRegistry_GetEntityByIndex(object->actorId);

        center = object->position;
        center.y += 0xc00;
        InitBoxShape(&shape, &storage, &center, &extent, &data_02053458);
        CollisionQuery_Init(&query, 0, actor, 8, 0, 0, &shape, &workspace, NULL);
        query.callback.func = func_ov016_020a41e0;
        query.callback.arg = object;
        SweepWorldCollision(&query);
    }
    if (object->flags & 0x1000) {
        pressed = 1;
    } else if (!(object->flags & 0x2000)) {
        pressed = 0;
    }
    if (pressed != object->pressed) {
        Actor *actor = ActorRegistry_GetEntityByIndex(object->actorId);
        World *world = GetActorRegistry();

        func_ov001_0208645c(object, pressed);
        if (pressed == 0) {
            scale = 0x1000;
            if (world != NULL && world->tree != NULL && (actor->flags & 0x10)) {
                actor->flags &= ~0x10;
                QuadTree_InsertObject(world->tree->root, actor->node);
            }
        } else {
            scale = 0xfc3;
            if (world != NULL && world->tree != NULL && !(actor->flags & 0x10)) {
                actor->flags |= 0x10;
                QuadTree_RemoveObject(world->tree->root, actor->node);
            }
        }
        actor->scale.x = actor->scale.y = actor->scale.z = scale;
    }
    enable = TRUE;
    if (pressed != 0) {
        enable = FALSE;
    }
    if (object->flags & 0x1000000) {
        enable = FALSE;
    }
    func_ov016_020a229c(object, enable);
    object->flags &= ~0x2000;
    if (done) {
        object->timer = 0;
    }
}
