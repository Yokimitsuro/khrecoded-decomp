#include "nitro/types.h"

typedef struct {
    u8 pad_000[0xb64];
    u8 labelTable[0x60];
    BOOL useAlternateFocus;
} PanelScene;

extern void *func_ov039_020bc1dc(void);
extern void ShowChoiceWindows(PanelScene *scene, int mode);
extern void *func_ov027_020ba2c8(void *table, int index);
extern void func_ov087_020c4734(PanelScene *scene, int slotIndex, void *label, int mode);
extern void *FindWidgetById(void *container, int elementId);
extern void SetFocusedWidget(void *container, void *element);
extern void MoveCursorToWidget(PanelScene *scene, void *element, int arg2, int arg3);

void OpenSelectionPanel(PanelScene *scene)
{
    void *container = func_ov039_020bc1dc();
    void *element;

    ShowChoiceWindows(scene, 2);
    func_ov087_020c4734(scene, 0, func_ov027_020ba2c8(scene->labelTable, 2), 2);
    func_ov087_020c4734(scene, 1, func_ov027_020ba2c8(scene->labelTable, 3), 2);
    element = !scene->useAlternateFocus ? FindWidgetById(container, 2) : FindWidgetById(container, 3);
    SetFocusedWidget(container, element);
    MoveCursorToWidget(scene, element, 0, 0);
}
