#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct NodeDef {
    u8 pad_00[8];
    u16 flags;
} NodeDef;

typedef struct LinkNode LinkNode;

struct LinkNode {
    LinkNode *next;
    u8 pad_04[4];
    NodeDef *def;
    u8 pad_0c[0x32 - 0x0c];
    u8 actorId;
    u8 pad_33[5];
    VecFx32 position;
};

typedef struct LinkList {
    u8 pad_00[8];
    LinkNode *head;
} LinkList;

typedef struct CollisionWorld {
    u8 pad_00[4];
    int **tree;
} CollisionWorld;

typedef struct LinkedActor {
    u32 flags;
    u8 pad_004[0x10c - 0x004];
    u8 collision[0xc];
    u8 collisionFlags;
    u8 pad_119[0x134 - 0x119];
    u8 baseBox[0x1c];
    VecFx32 offset;
    u8 box[0x18];
} LinkedActor;

extern LinkList *data_ov001_020a04fc;
extern const VecFx32 data_0205344c;

extern CollisionWorld *GetActorRegistry(void);
extern LinkedActor *ActorRegistry_GetEntityByIndex(u32 id);
extern BOOL IsNodeFlagBitClear(LinkNode *node);
extern void OffsetBoxByDelta(const void *src, void *dst, const VecFx32 *delta);
extern void SetCollisionObjectPosition(void *object, const VecFx32 *position);
extern void QuadTree_ReinsertNodeIfFlagSet(int *tree, void *node);

void ResetLinkedActorOffsets(void)
{
    LinkNode *node = data_ov001_020a04fc->head;
    CollisionWorld *world = GetActorRegistry();
    LinkNode *next;
    LinkedActor *actor;

    while (node != NULL) {
        next = node->next;
        if (IsNodeFlagBitClear(node) && (node->def->flags & 0x100)) {
            actor = ActorRegistry_GetEntityByIndex(node->actorId);
            if (world != NULL && !(actor->flags & 0x10) && (actor->flags & 8)) {
                actor->offset = data_0205344c;
                OffsetBoxByDelta(actor->baseBox, actor->box, &actor->offset);
                SetCollisionObjectPosition(actor->collision, &node->position);
                actor->collisionFlags |= 1;
                QuadTree_ReinsertNodeIfFlagSet(*world->tree, actor->collision);
            }
        }
        node = next;
    }
}
