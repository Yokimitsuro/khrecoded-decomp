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
    TextWindow choiceWindows[3];
    TextWindow confirmWindows[2];
    u8 pad_afc[0x74];
    PanelStackEntry stack[6];
    int depth;
    int selectedSlot;
} PanelScene;

typedef struct {
    int values[2];
} IdPair;

extern const IdPair data_ov087_020c7ca0;
extern u16 *UpdateScreenWidgetLayer(int bgId);
extern void *func_ov039_020bc1dc(void);
extern void FillBackgroundLayerRect(void *layer, u16 *dst, int x, int y, u8 palette);
extern void *FindWidgetById(void *container, int elementId);
extern void SetEntrySlotsVisible(void *container, void *element, BOOL visible);
extern void SetScreenLayerDirty(int layerId);
extern void SetFocusedWidget(void *container, void *widget);
extern void MoveCursorToWidget(PanelScene *scene, void *widget, BOOL narrow, BOOL playSound);

void ShowConfirmWindows(PanelScene *scene)
{
    u16 *tileMap = UpdateScreenWidgetLayer(10);
    int i;
    IdPair widgetIds = data_ov087_020c7ca0;
    void *container = func_ov039_020bc1dc();
    void *widget;

    for (i = 0; i < 2; i++) {
        if (scene->stack[scene->depth].stateId != 0x10) {
            FillBackgroundLayerRect(&scene->confirmWindows[i], tileMap, (u16)(i * 0xe + 3), 0x14, 0xf);
        }
        SetEntrySlotsVisible(container, FindWidgetById(container, widgetIds.values[i]), TRUE);
    }
    SetScreenLayerDirty(10);
    widget = FindWidgetById(container, 8);
    SetFocusedWidget(container, widget);
    MoveCursorToWidget(scene, widget, TRUE, FALSE);
    scene->selectedSlot = 1;
}
