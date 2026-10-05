#include "nitro/types.h"

typedef struct PanelElement {
    u8 pad_00[0xc];
    u32 value;
} PanelElement;

typedef struct MenuContext {
    u8 unk_00;
    u8 mode;
    u8 unk_02;
    s8 selectedIndex;
    u8 pad_04[4];
    s32 unk_08;
    u32 currentValue;
    u8 pad_10[0x69e8 - 0x10];
    u8 panel[0x6450];
} MenuContext;

extern MenuContext *data_ov002_0206c464;

extern PanelElement *FindWidgetById(void *panel, int elementId);
extern void SetEntrySlotsVisible(void *panel, PanelElement *element, BOOL visible);
extern void SetFocusedWidget(void *panel, PanelElement *element);
extern void ApplyWidgetFocusAnims(void *panel, PanelElement *element, BOOL enabled);
extern void func_ov027_020b9604(void *panel, PanelElement *element);
extern void func_ov027_020b90b8(void *panel, void (*callback)(PanelElement *element));
extern void ShowSaveMessage(int state);
extern void ApplyMenuEntryValues(int state);
extern void UpdateMenuSelectionSound(PanelElement *element);
extern BOOL PlaySoundEffect(int seqArcNo, int index);

void OpenMenuPopup(void)
{
    *(vu32 *)0x04001000 = (*(vu32 *)0x04001000 & ~0x1f00) | 0x1f00;
    SetEntrySlotsVisible(data_ov002_0206c464->panel, FindWidgetById(data_ov002_0206c464->panel, 0xb), TRUE);
    SetEntrySlotsVisible(data_ov002_0206c464->panel, FindWidgetById(data_ov002_0206c464->panel, 0xc), TRUE);
    ShowSaveMessage(1);
    SetFocusedWidget(data_ov002_0206c464->panel, FindWidgetById(data_ov002_0206c464->panel, 0xc));
    ApplyWidgetFocusAnims(data_ov002_0206c464->panel,
                        FindWidgetById(data_ov002_0206c464->panel, data_ov002_0206c464->selectedIndex + 1), TRUE);
    func_ov027_020b9604(data_ov002_0206c464->panel,
                        FindWidgetById(data_ov002_0206c464->panel, data_ov002_0206c464->selectedIndex + 1));
    func_ov027_020b90b8(data_ov002_0206c464->panel, UpdateMenuSelectionSound);
    data_ov002_0206c464->currentValue = FindWidgetById(data_ov002_0206c464->panel, 0xc)->value;
    PlaySoundEffect(2, 3);
    ApplyMenuEntryValues(0);
    data_ov002_0206c464->unk_02 = 0;
    data_ov002_0206c464->unk_08 = 0;
}
