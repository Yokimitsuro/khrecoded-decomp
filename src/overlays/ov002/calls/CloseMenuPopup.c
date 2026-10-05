#include "nitro/types.h"

typedef struct PanelElement PanelElement;

typedef struct MenuContext {
    u8 state;
    u8 mode;
    u8 unk_02;
    s8 selectedIndex;
    u8 pad_04[0x69e8 - 4];
    u8 panel[0x6450];
} MenuContext;

extern MenuContext *data_ov002_0206c464;

extern void DrawMenuLabels(void);
extern PanelElement *FindWidgetById(void *panel, int elementId);
extern void SetEntrySlotsVisible(void *panel, PanelElement *element, BOOL visible);
extern void ApplyMenuEntryValues(int state);
extern void SetFocusedWidget(void *panel, PanelElement *element);
extern void func_ov027_020b9640(void *panel, PanelElement *element);
extern void func_ov027_020b90b8(void *panel, void (*callback)(void));
extern void OnPopupElementTouched(void);
extern void func_ov002_02066a68(void);

void CloseMenuPopup(void)
{
    void *panel;

    *(vu32 *)0x04001000 = (*(vu32 *)0x04001000 & ~0x1f00) | 0x1e00;
    DrawMenuLabels();
    panel = data_ov002_0206c464->panel;
    SetEntrySlotsVisible(panel, FindWidgetById(data_ov002_0206c464->panel, 0xb), FALSE);
    panel = data_ov002_0206c464->panel;
    SetEntrySlotsVisible(panel, FindWidgetById(data_ov002_0206c464->panel, 0xc), FALSE);
    ApplyMenuEntryValues(1);
    panel = data_ov002_0206c464->panel;
    SetFocusedWidget(panel, FindWidgetById(data_ov002_0206c464->panel, data_ov002_0206c464->selectedIndex + 1));
    panel = data_ov002_0206c464->panel;
    func_ov027_020b9640(panel, FindWidgetById(data_ov002_0206c464->panel, data_ov002_0206c464->selectedIndex + 1));
    func_ov027_020b90b8(data_ov002_0206c464->panel, OnPopupElementTouched);
    func_ov002_02066a68();
}
