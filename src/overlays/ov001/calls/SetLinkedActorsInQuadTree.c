#include "nitro/types.h"

typedef struct CollisionWorld {
    u32 unk_00;
    void **quadTree;
} CollisionWorld;

extern void *GetFirstLinkedActor(void *actor);
extern void *GetNextLinkedActor(void *actor);
extern CollisionWorld *GetActorRegistry(void);
extern void QuadTree_InsertObject(void *quadTree, void *object);
extern void QuadTree_RemoveObject(void *quadTree, void *object);

void SetLinkedActorsInQuadTree(void *actor, BOOL insert)
{
    void *link;
    CollisionWorld *world;

    link = GetFirstLinkedActor(actor);
    world = GetActorRegistry();
    if (world == NULL) {
        return;
    }
    for (link = GetNextLinkedActor(link); link != NULL; link = GetNextLinkedActor(link)) {
        if (insert) {
            QuadTree_InsertObject(*world->quadTree, link);
        } else {
            QuadTree_RemoveObject(*world->quadTree, link);
        }
    }
}
