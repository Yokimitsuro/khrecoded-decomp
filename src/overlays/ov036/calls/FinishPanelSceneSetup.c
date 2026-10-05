#include "nitro/types.h"

typedef struct ScreenLayer {
    u8 pad_00[0x28];
    s32 imageId;
    u8 pad_2c[0x34 - 0x2c];
    s32 scrollX;
    s32 scrollY;
    u8 pad_3c[0x50 - 0x3c];
    s32 pendingImageId;
} ScreenLayer;

typedef struct SlotPoint {
    s32 x;
    s32 y;
} SlotPoint;

typedef struct SlotEntry {
    u8 pad_00[0x10];
    SlotPoint position;
    u8 pad_18[0x80 - 0x18];
    SlotPoint target;
    u8 pad_88[0x8c - 0x88];
    s32 ownerId;
    u8 pad_90[0x94 - 0x90];
    u32 recordId;
    u32 pendingRecordId;
} SlotEntry;

typedef struct SlotScene {
    u8 pad_0000[0x8];
    s32 state;
    u8 pad_000c[0x1090 - 0xc];
    SlotEntry *slots;
    void *actors;
    ScreenLayer *layers;
} SlotScene;

typedef struct SlotSceneHolder {
    u32 unk_00;
    SlotScene *scene;
} SlotSceneHolder;

extern SlotSceneHolder data_ov036_020c3940;
extern void SetScreenLayerImage(int screen, s32 imageId);
extern void ResetScreenLayer(int screen, s32 useWhiteClearColor);
extern void StartScreenLayerScroll(int screen, s32 x, s32 y, s32 duration);
extern BOOL SetSlotSharedRecord(int ownerId, u32 recordId);
extern void G2x_SetBlendAlpha_(void *reg, u32 plane1, u32 plane2, u32 ev1, u32 ev2);
extern void G3X_SetClearColor(u32 color, u32 alpha, u32 depth, u32 polygonId, BOOL fog);
extern void SetPanelEnabled(int value);

int FinishPanelSceneSetup(void)
{
    int i;
    SlotEntry *slot;
    SlotScene *scene = data_ov036_020c3940.scene;
    ScreenLayer *layer = scene->layers;

    if (layer->imageId != layer->pendingImageId) {
        if (layer->pendingImageId == -1) {
            ResetScreenLayer(0, 0);
        } else {
            SetScreenLayerImage(0, layer->pendingImageId);
        }
    }
    StartScreenLayerScroll(0, -layer->scrollX, layer->scrollY, 0);
    for (i = 0; i < 8; i++) {
        slot = &scene->slots[i];
        if (slot->ownerId != -1) {
            slot->position = slot->target;
            if (slot->recordId != slot->pendingRecordId) {
                SetSlotSharedRecord(slot->ownerId, slot->pendingRecordId);
                return -1;
            }
        }
    }
    G2x_SetBlendAlpha_((void *)0x04000050, 1, 0x22, 0, 0x10);
    G3X_SetClearColor(0, 0, 0x7fff, 0x3f, 0);
    SetPanelEnabled(1);
    scene->state = 3;
    return 3;
}
