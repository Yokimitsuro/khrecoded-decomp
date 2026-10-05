#include "nitro/types.h"

typedef struct {
    int stateId;
    void *focusElement;
} PanelStackEntry;

typedef struct {
    u8 pad_000[0xb30];
    u8 infoLayer[0x40];
    PanelStackEntry stack[6];
    int depth;
    u8 pad_ba4[0x8];
    BOOL infoVisible;
} PanelScene;

extern void *func_ov039_020bc1dc(void);
extern u16 *UpdateScreenWidgetLayer(int bgId);
extern void CallStateWidget(int bgId, int x, int y, int width, int height);
extern void SetScreenLayerDirty(int bgId);
extern void FillBackgroundLayerRect(void *layer, u16 *dst, int x, int y, u8 palette);
extern void Text_UploadTileBuffer(void *surface);
extern void *FindWidgetById(void *container, int elementId);
extern void SetEntrySlotsVisible(void *container, void *element, BOOL visible);

void SetInfoWindowVisible(PanelScene *scene, BOOL visible)
{
    void *container = func_ov039_020bc1dc();
    u16 *tileMap = UpdateScreenWidgetLayer(10);

    if (visible) {
        if (scene->stack[scene->depth].stateId != 0x10) {
            FillBackgroundLayerRect(scene->infoLayer, tileMap, 6, 0xf, 0xf);
            Text_UploadTileBuffer(scene->infoLayer);
        }
    } else {
        CallStateWidget(10, 6, 0xf, 0x14, 2);
    }
    SetEntrySlotsVisible(container, FindWidgetById(container, 0xd), visible);
    SetScreenLayerDirty(10);
    scene->infoVisible = visible;
}
