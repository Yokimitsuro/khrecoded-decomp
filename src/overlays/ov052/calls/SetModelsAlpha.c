#include "nitro/types.h"

typedef struct ModelHolder {
    u8 pad_00[0x7C];
    void *resModel;
} ModelHolder;

typedef struct ModelGroup {
    u8 pad_000[0x230];
    ModelHolder *mainModel;
    u8 pad_234[0x934];
    u32 slotFlags;
    u8 pad_B6C[0x7C];
    void *slotModel;
} ModelGroup;

extern void NNS_G3dMdlSetMdlAlphaAll(void *resModel, int alpha);

void SetModelsAlpha(ModelGroup *group, u32 alpha)
{
    ModelGroup *slot;
    int slotIndex;

    if (alpha > 31) {
        alpha = 31;
    }
    NNS_G3dMdlSetMdlAlphaAll(group->mainModel->resModel, (u8)alpha);
    slotIndex = 0;
    do {
        slot = (ModelGroup *)((u8 *)group + slotIndex * 0x230);
        if (slot->slotFlags & 1) {
            NNS_G3dMdlSetMdlAlphaAll(slot->slotModel, (u8)alpha);
        }
        slotIndex++;
    } while (slotIndex < 2);
}
