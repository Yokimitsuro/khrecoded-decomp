#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x34];
    u8 textLayer[0x34];
    s32 mode;
    u8 pad_06C[0x8];
    void *modeLabels[0x24];
    void *menuLabel;
    u8 pad_108[0x20];
    s32 shown;
    s32 dirty;
} FieldMenu;

typedef struct {
    u32 unk_00;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle data_ov001_020a04d0;

extern void *GetSceneTagTracker(void);
extern void *func_ov001_0207123c(void);
extern u16 *UpdateFieldWidgetLayer(int layerId);
extern void func_ov001_02078360(int a, int b);
extern void *FindActiveRecordById(void *pool, u32 recordId);
extern void func_ov027_020b8230(void *pool, void *record);
extern void func_ov027_020b8288(void *pool, void *record);
extern void func_ov001_02075e10(FieldMenu *menu, void *pool, void *label);
extern void SelectListNodeOrFirst(void *list, void *node);
extern void Text_UploadTileBuffer(void *text);
extern BOOL IsFieldFlag8Set(void);
extern void func_ov001_02078ac4(void);
extern BOOL HasFieldOverlayScreen(void);
extern void func_ov001_02076ebc(FieldMenu *menu, int arg);
extern void func_ov001_020769f4(FieldMenu *menu);
extern void FillBackgroundLayerRect(void *layer, u16 *dst, int x, int y, u8 palette);
extern void func_ov027_020b9e20(void *layers, int layerId);

void SetFieldMenuMode(int mode) {
    FieldMenu *menu = data_ov001_020a04d0.menu;
    void *pool = GetSceneTagTracker();
    void *layers = func_ov001_0207123c();
    u16 *dst = UpdateFieldWidgetLayer(0xb);
    BOOL refresh = FALSE;
    BOOL shown;

    switch (mode) {
    case -1:
        shown = FALSE;
        func_ov001_02078ac4();
        break;
    case 10:
        shown = TRUE;
        func_ov001_02078360(0, 1);
        func_ov027_020b8230(pool, FindActiveRecordById(pool, 0x24));
        func_ov001_02075e10(menu, pool, menu->menuLabel);
        func_ov027_020b8288(pool, FindActiveRecordById(pool, 0xc));
        func_ov027_020b8288(pool, FindActiveRecordById(pool, 0x55));
        SelectListNodeOrFirst(menu->textLayer, menu->modeLabels[mode]);
        Text_UploadTileBuffer(menu->textLayer);
        refresh = TRUE;
        break;
    default:
        if (menu->mode == 10) {
            func_ov027_020b8230(pool, FindActiveRecordById(pool, (u16)(IsFieldFlag8Set() ? 0xe : 0xc)));
            func_ov027_020b8230(pool, FindActiveRecordById(pool, 0x21));
            func_ov001_02075e10(menu, pool, menu->menuLabel);
            refresh = TRUE;
        }
        shown = TRUE;
        SelectListNodeOrFirst(menu->textLayer, menu->modeLabels[mode]);
        Text_UploadTileBuffer(menu->textLayer);
        func_ov001_02078ac4();
        break;
    }

    menu->mode = mode;
    menu->dirty = 1;
    if (!HasFieldOverlayScreen()) {
        func_ov001_02076ebc(menu, 0);
    }
    if (refresh) {
        func_ov001_020769f4(menu);
    }
    if ((shown && !menu->shown) || (!shown && menu->shown)) {
        FillBackgroundLayerRect(menu->textLayer, dst, 2, 0x16, 10);
        func_ov027_020b9e20(layers, 0xb);
        menu->shown = shown;
    }
}
