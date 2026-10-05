#include "nitro/types.h"

typedef struct {
    u8 data[0x34];
} TextWindow;

typedef struct {
    int stateId;
    void *focusElement;
} PanelStackEntry;

typedef struct {
    u8 pad_000[0x9f8];
    TextWindow windows[3];
    u8 pad_a94[0xdc];
    PanelStackEntry stack[6];
    int depth;
    int selectedSlot;
} PanelScene;

typedef struct {
    int values[3];
} IdTriple;

extern const IdTriple data_ov087_020c7ce4;
extern u16 *UpdateScreenWidgetLayer(int bgId);
extern void *func_ov039_020bc1dc(void);
extern void FillBackgroundLayerRect(void *layer, u16 *dst, int x, int y, u8 palette);
extern void *FindWidgetById(void *container, int elementId);
extern void SetEntrySlotsVisible(void *container, void *element, BOOL visible);
extern void ApplySelectedSubitemValues(void *container, void *element, BOOL useAlt);
extern void SetScreenLayerDirty(int layerId);

void ShowChoiceWindows(PanelScene *scene, int count)
{
    u16 *tileMap = UpdateScreenWidgetLayer(10);
    int i;
    IdTriple widgetIds = data_ov087_020c7ce4;
    void *container = func_ov039_020bc1dc();
    int widgetId;

    if (count > 3) {
        count = 3;
    }
    for (i = 0; i < count; i++) {
        if (scene->stack[scene->depth].stateId != 0x10) {
            FillBackgroundLayerRect(&scene->windows[i], tileMap, 8, (u16)(i * 2 + 0x11), 0xf);
        }
        widgetId = widgetIds.values[i];
        SetEntrySlotsVisible(container, FindWidgetById(container, widgetId), TRUE);
        ApplySelectedSubitemValues(container, FindWidgetById(container, widgetId), TRUE);
    }
    SetScreenLayerDirty(10);
    scene->selectedSlot = 0;
}



