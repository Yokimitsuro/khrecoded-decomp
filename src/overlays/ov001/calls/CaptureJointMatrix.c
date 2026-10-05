#include "nitro/types.h"
#include "nitro/fx.h"

typedef struct JointActor
{
    u8 pad_000[0x188];
    u32 jointId;
    MtxFx43 jointMatrix;
} JointActor;

typedef struct RenderOwner
{
    u8 pad_00[0x2C];
    JointActor *actor;
} RenderOwner;

typedef struct RenderNode
{
    u8 pad_00[0x4];
    RenderOwner *owner;
    u32 flags;
    u8 pad_0C[0xA2];
    u8 nodeId;
} RenderNode;

extern void NNS_G3dGetCurrentMtx(MtxFx43 *m, MtxFx33 *n);

void CaptureJointMatrix(RenderNode *node)
{
    JointActor *actor = node->owner->actor;
    u32 key = (node->flags & 0x10) ? node->nodeId : 0xFFFFFFFF;

    if (key == actor->jointId)
        NNS_G3dGetCurrentMtx(&actor->jointMatrix, NULL);
}
