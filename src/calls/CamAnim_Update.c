#include "nitro/types.h"

typedef struct RenderStateScratch {
    u8 bytes[0x188];
} RenderStateScratch;

typedef struct CameraAnim CameraAnim;

extern void CamAnim_ApplyPose(CameraAnim *anim);
extern RenderStateScratch *NNS_G3dRS;

void CamAnim_Update(CameraAnim *anim)
{
    RenderStateScratch scratch;

    if (NNS_G3dRS == NULL) {
        NNS_G3dRS = &scratch;
        CamAnim_ApplyPose(anim);
        NNS_G3dRS = NULL;
    } else {
        CamAnim_ApplyPose(anim);
    }
}
