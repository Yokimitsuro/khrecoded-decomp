#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x174];
    u8 flagTracker[0x1c];
} Ov086Menu;

extern u8 *func_ov039_020bc1ec(void);
extern void *FindWidgetById(u8 *panel, int elementId);
extern void SetEntrySlotsVisible(u8 *panel, void *element, BOOL visible);
extern void func_ov027_020b9d38(u8 *tracker, int id);
extern void CallStateWidget(int arg0, int arg1, int arg2, int arg3, int arg4);

void ShowSecondaryPanelElementE(Ov086Menu *menu)
{
    u8 *panel = func_ov039_020bc1ec();
    void *element;

    element = FindWidgetById(panel, 0x8);
    SetEntrySlotsVisible(panel, element, FALSE);
    element = FindWidgetById(panel, 0x14);
    SetEntrySlotsVisible(panel, element, FALSE);
    element = FindWidgetById(panel, 0x15);
    SetEntrySlotsVisible(panel, element, FALSE);
    element = FindWidgetById(panel, 0x2d);
    SetEntrySlotsVisible(panel, element, FALSE);
    element = FindWidgetById(panel, 0x2e);
    SetEntrySlotsVisible(panel, element, FALSE);
    element = FindWidgetById(panel, 0xa);
    SetEntrySlotsVisible(panel, element, FALSE);
    element = FindWidgetById(panel, 0xe);
    SetEntrySlotsVisible(panel, element, TRUE);
    func_ov027_020b9d38(menu->flagTracker, 0x19);
    CallStateWidget(0x18, 1, 0, 0xb, 2);
}
