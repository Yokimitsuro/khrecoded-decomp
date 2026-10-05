#include "nitro/types.h"

typedef struct ActorModel {
    u8 pad_00[0x78];
    void *modelResource;
} ActorModel;

extern void NNS_G3dMdlSetMdlCullModeAll(void *model, int cullMode);
extern void NNSi_G3dModifyPolygonAttrMask(void *model, BOOL enable, u32 mask);

void SetModelCullMode(ActorModel *actor, BOOL cullBack, BOOL cullNone)
{
    if (cullBack) {
        NNS_G3dMdlSetMdlCullModeAll(actor->modelResource, 2);
        return;
    }
    if (cullNone) {
        NNS_G3dMdlSetMdlCullModeAll(actor->modelResource, 3);
        return;
    }
    NNSi_G3dModifyPolygonAttrMask(actor->modelResource, TRUE, 0xc0);
}
