#include "nitro/types.h"

typedef struct {
    int values[2];
} IdPair;

typedef struct {
    u8 pad_000[0xb64];
    u8 labelTable[0xc];
} PanelScene;

extern const IdPair data_ov087_020c7c90;
extern void *func_ov039_020bc1dc(void);
extern void ShowChoiceWindows(PanelScene *scene, int count);
extern void *func_ov027_020ba2c8(void *table, int index);
extern void func_ov087_020c4734(PanelScene *scene, int windowIndex, void *text, int color);
extern void *FindWidgetById(void *container, int elementId);
extern void SetFocusedWidget(void *container, void *widget);
extern void MoveCursorToWidget(PanelScene *scene, void *widget, int slot, BOOL immediate);

void OpenTwoChoiceMenu(PanelScene *scene)
{
    void *container = func_ov039_020bc1dc();
    IdPair labels = data_ov087_020c7c90;
    void *widget;
    int i;

    ShowChoiceWindows(scene, 2);
    for (i = 0; i < 2; i++) {
        func_ov087_020c4734(scene, i, func_ov027_020ba2c8(scene->labelTable, labels.values[i]), 2);
    }
    widget = FindWidgetById(container, 3);
    SetFocusedWidget(container, widget);
    MoveCursorToWidget(scene, widget, 0, 0);
}
