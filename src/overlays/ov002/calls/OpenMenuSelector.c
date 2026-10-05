#include "nitro/types.h"

typedef struct PanelElement PanelElement;

typedef struct MenuContext {
    u8 state;
    u8 mode;
    u8 unk_02;
    s8 selectedIndex;
    u8 pad_04[4];
    s32 phase;
    u8 pad_0C[0x69e8 - 0xc];
    u8 panel[0x6450];
} MenuContext;

extern MenuContext *data_ov002_0206c464;

extern PanelElement *FindWidgetById(void *panel, int elementId);
extern void SetEntrySlotsVisible(void *panel, PanelElement *element, BOOL visible);
extern void ApplyMenuEntryValues(int state);
extern void ShowSaveMessage(int state);
extern void SetFocusedWidget(void *panel, PanelElement *element);
extern void ApplyWidgetFocusAnims(void *panel, PanelElement *element, BOOL enabled);
extern void func_ov027_020b9604(void *panel, PanelElement *element);
extern void func_ov027_020b90b8(void *panel, void (*callback)(void));
extern void UpdateMenuSelectionSound(void);
extern void func_ov002_020666c8(int value);

void OpenMenuSelector(void)
{
    void *panel;

    *(vu32 *)0x04001000 = (*(vu32 *)0x04001000 & ~0x1f00) | 0x1f00;
    panel = data_ov002_0206c464->panel;
    SetEntrySlotsVisible(panel, FindWidgetById(data_ov002_0206c464->panel, 0xb), TRUE);
    panel = data_ov002_0206c464->panel;
    SetEntrySlotsVisible(panel, FindWidgetById(data_ov002_0206c464->panel, 0xc), TRUE);
    ApplyMenuEntryValues(0);
    ShowSaveMessage(3);
    SetFocusedWidget(data_ov002_0206c464->panel, FindWidgetById(data_ov002_0206c464->panel, 0xc));
    panel = data_ov002_0206c464->panel;
    ApplyWidgetFocusAnims(panel, FindWidgetById(data_ov002_0206c464->panel, data_ov002_0206c464->selectedIndex + 1), TRUE);
    panel = data_ov002_0206c464->panel;
    func_ov027_020b9604(panel, FindWidgetById(data_ov002_0206c464->panel, data_ov002_0206c464->selectedIndex + 1));
    func_ov027_020b90b8(data_ov002_0206c464->panel, UpdateMenuSelectionSound);
    data_ov002_0206c464->phase = 0;
    data_ov002_0206c464->unk_02 = 0;
    func_ov002_020666c8(0);
}
