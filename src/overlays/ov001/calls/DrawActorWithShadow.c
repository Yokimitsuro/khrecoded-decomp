#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ActorNode {
    u32 flags;
    u8 node[0x20];
    u32 renderFlags;
    u8 pad_28[0x28];
    void *owner;
} ActorNode;

typedef struct ShadowOwner {
    u8 pad_000[0x1a8];
    VecFx32 shadowPosition;
} ShadowOwner;

typedef struct ShadowedActor {
    u8 pad_00[0xc];
    ShadowOwner *owner;
    u8 pad_10[0x28];
    u8 actorId;
    u8 pad_39[0x4b];
    u16 animFlags;
    u8 pad_86[0x1e];
    u8 renderObj[0xdc];
    u16 colorScale;
    u8 pad_182[0xa];
    u32 geometryArgs[3];
} ShadowedActor;

extern ActorNode *ActorRegistry_GetEntityByIndex(u32 id);
extern void NNS_G3dRenderObjResetCallBack(void *renderObj);
extern void NNS_G3dRenderObjSetCallBack(void *renderObj, void *func, u8 *arg, u8 cmd, int timing);
extern void func_01ffb12c(void *node);
extern signed char func_ov001_02068084(void);
extern u16 AdvanceAnimationTracks(void *state, fx32 delta);
extern void NNS_G3dGlbFlushP(void);
extern void func_01fff67c(int packedRgb);
extern void NNS_G3dGeBufferOP_N(u32 op, const u32 *args, u32 numWords);
extern void func_01ffe1bc(void *renderObj);
extern void SweepShadowToGround(ShadowedActor *actor, VecFx32 *out);
extern void ShadowVolume_Draw(void *shadow);
extern void CaptureJointMatrix();

void DrawActorWithShadow(ShadowedActor *actor)
{
    ActorNode *node;
    VecFx32 position;

    node = ActorRegistry_GetEntityByIndex(actor->actorId);
    node->owner = actor;
    NNS_G3dRenderObjResetCallBack(&node->renderFlags);
    NNS_G3dRenderObjSetCallBack(&node->renderFlags, CaptureJointMatrix, NULL, 6, 3);
    node->renderFlags |= 1;
    if (!(node->flags & 0x20)) {
        func_01ffb12c(node->node);
    }
    node->renderFlags &= ~1;
    if (func_ov001_02068084() != 7) {
        AdvanceAnimationTracks(&actor->animFlags, 0x1000);
        NNS_G3dGlbFlushP();
        if (actor->animFlags & 0x40) {
            func_01fff67c(actor->colorScale);
        }
        NNS_G3dGeBufferOP_N(0x17, actor->geometryArgs, 0xc);
        func_01ffe1bc(actor->renderObj);
    }
    SweepShadowToGround(actor, &position);
    actor->owner->shadowPosition = position;
    ShadowVolume_Draw(&actor->owner->shadowPosition);
}
