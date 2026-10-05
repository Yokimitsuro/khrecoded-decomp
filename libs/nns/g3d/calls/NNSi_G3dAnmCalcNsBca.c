#include "libs/nns/g3d/g3d_nsbca_internal.h"

extern void getJntSRTAnmResult_(
    const NNSG3dResJntAnm *animation,
    u32 dataIndex,
    fx32 frame,
    NNSG3dJntAnmResult *result);

void NNSi_G3dAnmCalcNsBca(
    NNSG3dJntAnmResult *result,
    const NNSG3dAnmObj *animationObject,
    u32 dataIndex)
{
    fx32 frame;
    NNSG3dResJntAnm *animation =
        (NNSG3dResJntAnm *)animationObject->resAnm;

    if (animationObject->frame >= (animation->numFrame << FX32_SHIFT)) {
        frame = (animation->numFrame << FX32_SHIFT) - 1;
    } else if (animationObject->frame < 0) {
        frame = 0;
    } else {
        frame = animationObject->frame;
    }

    getJntSRTAnmResult_(animation, dataIndex, frame, result);
}
