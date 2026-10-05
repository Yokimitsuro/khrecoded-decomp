#include "nitro/types.h"

typedef struct {
    void *slots;
    s8 slotCount;
} EffectPool;

typedef struct {
    u8 pad_000[0xbc];
    void *model;
    u8 pad_0c0[0x18c - 0xc0];
    EffectPool effectPool;
    s32 variant;
} VariantActor;

extern void NNS_G3dMdlSetMdlCullMode(void *model, u32 materialIndex, int cullMode);
extern void UpdateSceneGroupNodes(VariantActor *actor);
extern void DrawModelSlots(EffectPool *pool);

void DrawWithVariantMaterialsHidden(VariantActor *actor)
{
    int materialIndex;
    int endMaterial;
    int firstMaterial;

    if (actor->variant > 0) {
        switch (actor->variant) {
        case 1:
            firstMaterial = 5;
            endMaterial = 6;
            break;
        case 2:
            firstMaterial = 9;
            endMaterial = 15;
            break;
        case 3:
            firstMaterial = 9;
            endMaterial = 23;
            break;
        }
        for (materialIndex = firstMaterial; materialIndex < endMaterial; materialIndex++) {
            NNS_G3dMdlSetMdlCullMode(actor->model, materialIndex, 0);
        }
    }
    UpdateSceneGroupNodes(actor);
    if (actor->variant > 0) {
        for (; firstMaterial < endMaterial; firstMaterial++) {
            NNS_G3dMdlSetMdlCullMode(actor->model, firstMaterial, 3);
        }
    }
    DrawModelSlots(&actor->effectPool);
}
