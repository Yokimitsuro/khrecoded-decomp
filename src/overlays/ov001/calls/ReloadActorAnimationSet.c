#include "nitro/types.h"

typedef struct {
    u32 unk0;
    u8 model[0xd8];
    u8 animSet[4];
} ActorRender;

typedef struct {
    u8 pad_000[0x10];
    ActorRender render;
    u8 pad_0f0[0x27e - 0xf0];
    u16 stageObjectId;
    u8 pad_280[0xa];
    u16 unk28a_0 : 14;
    u16 hasAnimations : 1;
    u16 unk28a_15 : 1;
    u8 pad_28c[0x3c4 - 0x28c];
    u8 *archive;
} StageActor;

extern void *GetStageObjectRecord(u32 id);
extern void ReleaseActorAnimationSet(void *animSet, void *model);
extern void LoadActorAnimationSet(void *animSet, void *model, int archiveId);

BOOL ReloadActorAnimationSet(StageActor *actor, u32 resourceIndex)
{
    ActorRender *render = &actor->render;

    if (!actor->hasAnimations) {
        return FALSE;
    }
    if (actor->archive == NULL) {
        return FALSE;
    }
    if (GetStageObjectRecord(actor->stageObjectId) == NULL) {
        return FALSE;
    }
    ReleaseActorAnimationSet(render->animSet, render->model);
    LoadActorAnimationSet(render->animSet, render->model, ((((u32)actor->archive + 0x8000) & 0xfffffc) << 7 | 0x80000000) | (resourceIndex & 0x1ff));
    return TRUE;
}
