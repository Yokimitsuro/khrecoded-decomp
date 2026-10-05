#include "nitro/types.h"

typedef struct ShadowModel {
    u8 pad_00[0x78];
    void *resModel;
    u8 pad_7C[0x88];
} ShadowModel;

typedef struct ObjectManager {
    u8 pad_000[0x14];
    u8 flags;
    u8 pad_015[0x107];
    ShadowModel *shadowModel;
} ObjectManager;

extern ObjectManager *data_ov001_020a04f8;
extern char sOv001_MoSdZ_0209f040[];
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void InitSharedRecordAndDispatch(void *dst, const char *path, void *info, int b);
extern void NNS_G3dMdlSetMdlAlphaAll(void *resModel, int alpha);

void ObjectManager_LoadShadowModel(void)
{
    ObjectManager *manager;

    manager = data_ov001_020a04f8;
    manager->flags |= 2;
    manager->shadowModel = NNSi_FndAllocFromDefaultHeap(sizeof(ShadowModel));
    InitSharedRecordAndDispatch(manager->shadowModel, sOv001_MoSdZ_0209f040, (void *)1, 3);
    NNS_G3dMdlSetMdlAlphaAll(manager->shadowModel->resModel, 8);
}
