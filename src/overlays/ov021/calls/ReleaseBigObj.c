#include "nitro/types.h"

extern void NNS_G3dRenderObjResetCallBack(void *renderObj);
extern void ReleaseResourceAndDetach(u8 *object);
extern void ReleaseSharedRecordState(void *state);

void ReleaseBigObj(u8 *obj)
{
    NNS_G3dRenderObjResetCallBack(obj + 0x20);
    ReleaseResourceAndDetach(obj);
    ReleaseSharedRecordState(obj + 0x104);
}
