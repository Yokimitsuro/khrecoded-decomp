#include "nitro/types.h"

typedef struct ActorModel {
    u8 pad_00[0x78];
    void *modelResource;
    u8 pad_7c[0x44];
    struct ActorModel *child;
    struct ActorModel *next;
} ActorModel;

typedef struct Actor {
    u32 unk_00;
    ActorModel model;
} Actor;

typedef struct PartyEntry {
    u8 pad_000[0x204];
    void (*setAlpha)(struct PartyEntry *entry, u8 alpha);
} PartyEntry;

extern u32 ActorRegistry_GetEntityByIndex(u32 actorId);
extern PartyEntry *GetBoundedEntryField(int index);
extern void SetModelCullMode(ActorModel *actor, BOOL cullBack, BOOL cullNone);
extern void NNS_G3dMdlSetMdlAlphaAll(void *model, int alpha);

void SetActorModelAlpha(int actorId, int alpha, BOOL cullBack)
{
    Actor *actor = (Actor *)ActorRegistry_GetEntityByIndex((u16)actorId);
    ActorModel *root;
    ActorModel *part;

    if (actorId < 3) {
        PartyEntry *entry = GetBoundedEntryField(actorId);
        SetModelCullMode(&actor->model, cullBack, TRUE);
        if (entry->setAlpha != NULL) {
            entry->setAlpha(entry, (u8)alpha);
        }
        return;
    }
    root = &actor->model;
    SetModelCullMode(root, cullBack, FALSE);
    NNS_G3dMdlSetMdlAlphaAll(root->modelResource, alpha);
    part = root->child;
    if (part != NULL) {
        NNS_G3dMdlSetMdlAlphaAll(part->modelResource, alpha);
        SetModelCullMode(part, cullBack, FALSE);
        for (part = part->next; part != NULL; part = part->next) {
            NNS_G3dMdlSetMdlAlphaAll(part->modelResource, alpha);
            SetModelCullMode(part, cullBack, FALSE);
        }
    }
}
