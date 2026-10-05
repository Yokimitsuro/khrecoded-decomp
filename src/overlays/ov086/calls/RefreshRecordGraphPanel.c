#include "nitro/types.h"

typedef struct {
    u8 pad_000[0xc];
    u8 textLayer[0x34];
    u8 listLayer[0xb8];
    void *selectedNode;
    u8 pad_0fc[0x134 - 0xfc];
    int pageIndex;
    u8 pad_138[4];
    int stepCount;
    int itemId;
    u8 pad_144[0xc];
    BOOL arrowsVisible;
    u8 pad_154[0x174 - 0x154];
    u8 screenLayers[0x1c];
    u8 recordPool[0x10];
} Ov086Menu;

typedef struct {
    s32 x;
    s32 y;
} ElementOffset;

extern u8 *func_ov039_020bc1ec(void);
extern void *FindWidgetById(u8 *panel, int elementId);
extern void SetEntrySlotsVisible(u8 *panel, void *element, BOOL visible);
extern void func_ov027_020b91e8(u8 *panel, void *element, ElementOffset *offset, int flags);
extern void ShowPrimaryRecordList(Ov086Menu *menu);
extern void *FindActiveRecordById(void *pool, u32 recordId);
extern void func_ov027_020b8230(void *pool, void *record);
extern void SelectListNodeOrFirst(void *self, void *target);
extern void Text_UploadTileBuffer(void *surface);
extern u16 *UpdateScreenWidgetLayer(int layerId);
extern void SetScreenLayerDirty(int layerId);
extern void FillBackgroundLayerRect(void *info, u16 *dst, int x, int y, u8 palette);
extern u16 *func_ov027_020b9e10(u8 *layers, int layerId);
extern void func_ov027_020b9e20(u8 *layers, int layerId);

void RefreshRecordGraphPanel(Ov086Menu *menu)
{
    u8 *panel = func_ov039_020bc1ec();
    ElementOffset offset = {0, 0};

    if (menu->stepCount > 1) {
        menu->stepCount = 1;
    }
    SetEntrySlotsVisible(panel, FindWidgetById(panel, 0xe), FALSE);
    SetEntrySlotsVisible(panel, FindWidgetById(panel, 0x8), TRUE);
    if (menu->stepCount == 0) {
        ShowPrimaryRecordList(menu);
    } else {
        func_ov027_020b8230(menu->recordPool, FindActiveRecordById(menu->recordPool, 0x3ee));
        SetEntrySlotsVisible(panel, FindWidgetById(panel, 0x14), FALSE);
        SetEntrySlotsVisible(panel, FindWidgetById(panel, 0x15), FALSE);
        SetEntrySlotsVisible(panel, FindWidgetById(panel, 0x2d), FALSE);
        SetEntrySlotsVisible(panel, FindWidgetById(panel, 0x2e), FALSE);
        SelectListNodeOrFirst(menu->listLayer, menu->selectedNode);
        Text_UploadTileBuffer(menu->listLayer);
    }
    offset.x = menu->stepCount << 16;
    func_ov027_020b91e8(panel, FindWidgetById(panel, 0xa), &offset, 4);
    SetEntrySlotsVisible(panel, FindWidgetById(panel, 0xa), TRUE);
    FillBackgroundLayerRect(menu->listLayer, UpdateScreenWidgetLayer(0x18), 1, 0, 0xf);
    SetScreenLayerDirty(0x18);
    FillBackgroundLayerRect(menu->textLayer, func_ov027_020b9e10(menu->screenLayers, 0x19), 3, 3, 0xf);
    func_ov027_020b9e20(menu->screenLayers, 0x19);
}
