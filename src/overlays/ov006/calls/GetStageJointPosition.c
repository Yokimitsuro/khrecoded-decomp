#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    fx32 x, y, z, w;
} Quaternion;

typedef struct {
    u32 flag;
} RenderObj;

typedef struct {
    u8 pad_00[0x20];
    RenderObj renderObj;
    u8 pad_24[0xb4];
    u8 blendTable[4];
} StageModel;

typedef struct {
    u8 pad_00[0xc];
    StageModel model;
} StageObjectRecord;

typedef struct {
    s16 animId;
    u8 pad_02[2];
} JointAnimEntry;

typedef struct {
    u8 pad_00;
    s8 animIndex;
    u8 pad_02[2];
    JointAnimEntry anims[4];
    fx32 frame;
    u8 pad_18[4];
    VecFx32 offset;
} JointAnimRequest;

extern const Quaternion data_ov006_020a1874;

extern u16 FindStageObjectByOwner(u16 slot, u32 owner);
extern StageObjectRecord *GetStageObjectRecord(u32 id);
extern void selectJointAnimationBlend(void *animationState, u16 trackIndex, void *blendTable, s16 blendIndex);
extern int *func_01ffb2f8(void *state, int track, int frame);
extern u16 AdvanceAnimationTracks(void *state, fx32 delta);
extern void SceneNode_DrawImmediate(void *node);
extern BOOL NNS_G3dGetResultMtx(const RenderObj *renderObj, MtxFx43 *pos, MtxFx33 *nrm, u32 nodeId);
extern void QuaternionFromRotationMatrix(Quaternion *quat, const MtxFx43 *mtx);
extern int ScaleVector4ByReciprocalMagnitude(Quaternion *vector, Quaternion *source);
extern void MultiplyFixedPointQuaternions(Quaternion *result, const Quaternion *left, const Quaternion *right);
extern void QuaternionToRotationMatrix(MtxFx43 *matrix, const Quaternion *quat);

void GetStageJointPosition(JointAnimRequest *request, VecFx32 *out) {
    StageModel *model = &GetStageObjectRecord(FindStageObjectByOwner(0, 2))->model;
    MtxFx43 mtx;
    Quaternion quat;
    JointAnimEntry *entry = &request->anims[request->animIndex];

    model->renderObj.flag |= 4;
    selectJointAnimationBlend(model, 0, model->blendTable, entry->animId);
    func_01ffb2f8(model, 0, request->frame);
    AdvanceAnimationTracks(model, 0);
    SceneNode_DrawImmediate(model);
    if (NNS_G3dGetResultMtx(&model->renderObj, &mtx, NULL, 0)) {
        QuaternionFromRotationMatrix(&quat, &mtx);
        ScaleVector4ByReciprocalMagnitude(&quat, &quat);
        MultiplyFixedPointQuaternions(&quat, &quat, &data_ov006_020a1874);
        QuaternionToRotationMatrix(&mtx, &quat);
    }
    out->x = request->offset.x + mtx._30;
    out->y = request->offset.y + mtx._31;
    out->z = request->offset.z + mtx._32;
    model->renderObj.flag &= ~4;
}
