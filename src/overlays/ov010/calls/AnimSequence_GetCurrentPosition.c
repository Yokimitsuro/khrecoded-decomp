#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    s16 animId;
    s16 loopCount;
} AnimSequenceClip;

typedef struct {
    s8 state;
    s8 clipIndex;
    s8 clipCount;
    s8 loopCounter;
    AnimSequenceClip clips[4];
    fx32 frame;
    u8 pad_18[0x04];
    VecFx32 position;
    VecFx32 target;
    VecFx32 startPosition;
} AnimSequence;

typedef struct {
    u8 animState[0x20];
    u32 renderFlags;
    u8 pad_24[0xd8 - 0x24];
    u8 blendTable[4];
} ActorModel;

typedef struct {
    u8 pad_00[0x0c];
    ActorModel model;
} StageObjectRecord;

typedef struct {
    fx32 x, y, z, w;
} Quat;

extern u16 FindStageObjectByOwner(u16 slot, u32 owner);
extern StageObjectRecord *GetStageObjectRecord(u32 id);
extern void selectJointAnimationBlend(void *animationState, u16 trackIndex, void *blendTable, s16 blendIndex);
extern int *func_01ffb2f8(void *animationState, int trackIndex, int frame);
extern u16 AdvanceAnimationTracks(void *animationState, fx32 delta);
extern void SceneNode_DrawImmediate(ActorModel *model);
extern BOOL NNS_G3dGetResultMtx(void *renderObj, MtxFx43 *pos, MtxFx33 *nrm, u32 nodeID);
extern void QuaternionFromRotationMatrix(Quat *quat, const MtxFx43 *mtx);
extern int ScaleVector4ByReciprocalMagnitude(Quat *vector, Quat *source);
extern void MultiplyFixedPointQuaternions(Quat *result, const Quat *left, const Quat *right);
extern void QuaternionToRotationMatrix(MtxFx43 *matrix, const Quat *quat);
extern const Quat data_ov010_020a1d7c;

void AnimSequence_GetCurrentPosition(AnimSequence *seq, VecFx32 *out)
{
    MtxFx43 mtx;
    Quat quat;
    ActorModel *model;
    AnimSequenceClip *clip;

    model = &GetStageObjectRecord(FindStageObjectByOwner(0, 2))->model;
    clip = &seq->clips[seq->clipIndex];
    model->renderFlags |= 4;
    selectJointAnimationBlend(model, 0, model->blendTable, clip->animId);
    func_01ffb2f8(model, 0, seq->frame);
    AdvanceAnimationTracks(model, 0);
    SceneNode_DrawImmediate(model);
    if (NNS_G3dGetResultMtx(&model->renderFlags, &mtx, NULL, 0)) {
        QuaternionFromRotationMatrix(&quat, &mtx);
        ScaleVector4ByReciprocalMagnitude(&quat, &quat);
        MultiplyFixedPointQuaternions(&quat, &quat, &data_ov010_020a1d7c);
        QuaternionToRotationMatrix(&mtx, &quat);
    }
    out->x = seq->position.x + mtx._30;
    out->y = seq->position.y + mtx._31;
    out->z = seq->position.z + mtx._32;
    model->renderFlags &= ~4;
}
