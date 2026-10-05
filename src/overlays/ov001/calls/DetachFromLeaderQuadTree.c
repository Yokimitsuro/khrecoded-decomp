#include "nitro/types.h"

typedef struct FieldState {
    u8 pad_000[0x20a];
    s16 leaderId;
} FieldState;

typedef struct ActorBody {
    u8 pad_000[0x11c];
    u8 quadNode[4];
} ActorBody;

typedef struct FieldActor {
    u8 pad_00[0xc];
    ActorBody *body;
    u8 pad_10[0x6e];
    s8 actorId;
} FieldActor;

typedef struct ActorCollision {
    int *quadTree;
} ActorCollision;

typedef struct ActorRecord {
    u8 pad_00[4];
    ActorCollision *collision;
} ActorRecord;

extern FieldState *data_ov001_020a0480;

extern ActorRecord *GetActorRegistry(int actorId);
extern void QuadTree_RemoveObject(int *tree, void *node);

BOOL DetachFromLeaderQuadTree(FieldActor *actor)
{
    ActorRecord *record;

    if (actor->actorId == data_ov001_020a0480->leaderId) {
        return TRUE;
    }
    record = GetActorRegistry(data_ov001_020a0480->leaderId);
    if (record != NULL && record->collision != NULL) {
        QuadTree_RemoveObject(record->collision->quadTree, actor->body->quadNode);
    }
    return FALSE;
}
