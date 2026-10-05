#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct GroupObject {
    u8 pad_00[0x32];
    u8 actorId;
    u8 pad_33[5];
    VecFx32 position;
    u8 pad_44[0x40];
    u8 collisionShape[4];
} GroupObject;

typedef struct ActorBody {
    u32 flags;
    u8 pad_04[0xa4];
    VecFx32 position;
    u8 pad_b4[0x58];
    u8 collision[0xc];
    u8 collisionFlags;
    u8 pad_119[0x1b];
    u8 bounds[0x1c];
    VecFx32 delta;
    u8 localBounds[0x18];
} ActorBody;

typedef struct World {
    u8 pad_00[4];
    void **quadTree;
} World;

extern void *func_ov032_020bbc98(GroupObject *object);
extern ActorBody *ActorRegistry_GetEntityByIndex(int actorId);
extern World *GetActorRegistry(void);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void OffsetBoxByDelta(void *out, const void *box, const VecFx32 *delta);
extern void SetCollisionObjectPosition(void *collision, const void *shape);
extern void QuadTree_ReinsertNodeIfFlagSet(void *tree, void *node);

void MoveGroupObjectAndSyncActor(GroupObject *object, const VecFx32 *delta)
{
    ActorBody *actor;
    World *world;

    func_ov032_020bbc98(object);
    actor = ActorRegistry_GetEntityByIndex(object->actorId);
    world = GetActorRegistry();
    VEC_Add(&object->position, delta, &object->position);
    actor->position = object->position;
    actor->delta = *delta;
    OffsetBoxByDelta(actor->bounds, actor->localBounds, &actor->delta);
    SetCollisionObjectPosition(actor->collision, object->collisionShape);
    if (world != NULL && !(actor->flags & 0x10) && (actor->flags & 8)) {
        actor->collisionFlags |= 1;
        QuadTree_ReinsertNodeIfFlagSet(*world->quadTree, actor->collision);
    }
}
