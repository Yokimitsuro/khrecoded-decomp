#include "nitro/types.h"

typedef struct ReleasableActor {
    u8 pad_000[0x14];
    u8 animationModel[0xd8];
    u8 animationSet[0xe4];
    u8 motionController[0xac];
    u16 typeId;
    u8 pad_27e[0x2];
    u16 unk_280;
    u8 pad_282[0x8];
    u16 unk_28A_0 : 14;
    u16 ownsAnimationSet : 1;
    u16 unk_28A_15 : 1;
    u8 pad_28c[0x120];
    u16 unk_3AC;
    u16 unk_3AE;
    u8 pad_3b0[0x14];
    void *extraBuffer;
} ReleasableActor;

extern void ReleaseAllAttachments(ReleasableActor *actor);
extern void ReleaseActorAttachments(ReleasableActor *actor);
extern void func_ov001_02091ae8(ReleasableActor *actor, u16 groupId, u16 effectId, int mode);
extern void FreeOwnedBuffer(void *controller);
extern void ReleaseActorAnimationSet(void *animationSet, void *model);
extern void ShutdownStageObject(ReleasableActor *actor);
extern void ActorRegistry_UnregisterSlot(ReleasableActor *actor);
extern int ZeroHalfThenFree(void *buffer);

BOOL ReleaseActorResources(ReleasableActor *actor)
{
    actor->unk_3AC = 0;
    actor->unk_3AE = 0;
    actor->unk_280 = 0;
    if (actor->typeId != 0) {
        ReleaseAllAttachments(actor);
        ReleaseActorAttachments(actor);
        func_ov001_02091ae8(actor, 0xffff, 0xffff, 0);
        FreeOwnedBuffer(actor->motionController);
        if (actor->ownsAnimationSet) {
            ReleaseActorAnimationSet(actor->animationSet, actor->animationModel);
        }
        ShutdownStageObject(actor);
        if (actor->typeId != 0xffff) {
            ActorRegistry_UnregisterSlot(actor);
        }
        if (actor->extraBuffer != NULL) {
            ZeroHalfThenFree(actor->extraBuffer);
            actor->extraBuffer = NULL;
            actor->ownsAnimationSet = FALSE;
        }
        actor->typeId = 0;
    }
    return TRUE;
}
