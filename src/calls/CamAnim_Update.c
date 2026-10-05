#include "nitro/types.h"

typedef struct RenderStateScratch {
    u8 bytes[0x188];
} RenderStateScratch;

typedef struct CameraAnim CameraAnim;

extern void func_0203a9f0(CameraAnim *anim);
extern RenderStateScratch *NNS_G3dRS;

void CamAnim_Update(CameraAnim *anim)
{
    RenderStateScratch scratch;

    if (NNS_G3dRS == NULL) {
        NNS_G3dRS = &scratch;
        func_0203a9f0(anim);
        NNS_G3dRS = NULL;
    } else {
        func_0203a9f0(anim);
    }
}
