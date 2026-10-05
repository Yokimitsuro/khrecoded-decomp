#include "nitro/types.h"

typedef struct FieldManager {
    u8 pad_000[0x47c];
    s32 panelState;
    u32 unk_480_0 : 9;
    u32 splitScreenMode : 1;
    u32 unk_480_10 : 22;
} FieldManager;

typedef struct FieldManagerHandle {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

typedef struct ScreenPiece {
    u16 id;
    u8 pad_02[0xe];
    s32 layer;
} ScreenPiece;

extern FieldManagerHandle data_ov001_020a04c4;
extern void *GetFieldLayerScreen(s32 layer);
extern void func_ov027_020b9bb4(FieldManager *manager, ScreenPiece *piece, void *layerScreen);
extern void ClearWidgetScreenRegion(FieldManager *manager, ScreenPiece *piece, void *layerScreen);

void ClearFieldScreenPiece(ScreenPiece *piece)
{
    FieldManager *manager = data_ov001_020a04c4.manager;
    void *layerScreen = GetFieldLayerScreen(piece->layer);
    u16 id = piece->id;

    if ((id >= 0x3a && id <= 0x45) || (id >= 600 && id <= 602) || (id >= 100 && id <= 0x6f) ||
        (id >= 0x104 && id <= 0x10f) || (id >= 500 && id <= 0x236)) {
        if (manager->panelState >= 1 && manager->panelState <= 3) {
            func_ov027_020b9bb4(data_ov001_020a04c4.manager, piece, layerScreen);
        }
        return;
    }
    if (manager->splitScreenMode == 1) {
        if (layerScreen != NULL && id >= 0x33 && id <= 0x39) {
            ClearWidgetScreenRegion(manager, piece, layerScreen);
        } else {
            func_ov027_020b9bb4(manager, piece, layerScreen);
        }
    } else if (layerScreen == NULL) {
        func_ov027_020b9bb4(manager, piece, layerScreen);
    } else {
        ClearWidgetScreenRegion(manager, piece, layerScreen);
    }
}
