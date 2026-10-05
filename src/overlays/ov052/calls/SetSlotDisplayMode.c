#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SlotActor SlotActor;
typedef int (*GetModeFunc)(SlotActor *actor);

typedef struct {
    u8 pad_00[0xd8];
    u8 blendTable[0x104 - 0xd8];
} SlotModel;

struct SlotActor {
    u8 pad_000[0x1dc];
    int mode;
    u8 pad_1e0[0x22c - 0x1e0];
    GetModeFunc getMode;
    u8 pad_230[0x9f0 - 0x230];
    fx32 slotScale;
    u8 pad_9f4[0x105c - 0x9f4];
    u8 activeBlock[0x10];
    SlotModel *models;
};

extern void selectJointAnimationBlend(void *selector, u16 trackIndex, void *blendTable, s16 blendIndex);
extern void func_ov052_020ca330(void *block);
extern void ResetGaugeDisplay(void);

void SetSlotDisplayMode(SlotActor *actor, int mode)
{
    void *block = actor->activeBlock;
    int current;
    int i;

    if (actor->getMode != NULL) {
        current = actor->getMode(actor);
    } else {
        current = actor->mode;
    }
    if (mode == current) {
        return;
    }
    if (current == 5) {
        actor->slotScale = 0x1000;
    }
    func_ov052_020ca330(block);
    switch (mode) {
    case 1:
        for (i = 0; i < 5; i++) {
            SlotModel *model = &actor->models[0];
            selectJointAnimationBlend(model, i, model->blendTable, 0);
        }
        break;
    case 2:
        for (i = 0; i < 5; i++) {
            SlotModel *model = &actor->models[1];
            selectJointAnimationBlend(model, i, model->blendTable, 0);
        }
        break;
    case 3:
        for (i = 0; i < 5; i++) {
            SlotModel *model = &actor->models[2];
            selectJointAnimationBlend(model, i, model->blendTable, 0);
        }
        break;
    case 4:
        for (i = 0; i < 5; i++) {
            SlotModel *model = &actor->models[3];
            selectJointAnimationBlend(model, i, model->blendTable, 0);
        }
        break;
    case 5:
        actor->slotScale = 0x800;
        break;
    case 10:
        ResetGaugeDisplay();
        break;
    }
    actor->mode = mode;
}
