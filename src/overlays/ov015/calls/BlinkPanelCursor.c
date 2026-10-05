#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ElementPos {
    fx32 x;
    fx32 y;
} ElementPos;

typedef struct PanelElement {
    u8 pad_00[0x94];
    u32 hiddenBit : 1;
    u32 visible : 1;
    u32 otherBits : 30;
} PanelElement;

typedef struct PanelState {
    u8 pad_0000[0xc0];
    s8 blinkTimer;
    u8 pad_00c1[0x20];
    u8 lowFlags : 5;
    u8 screenMode : 2;
    u8 highFlag : 1;
    u8 pad_00e1[0x562];
    u8 subPanel[0x647c];
    u8 panel[1];
} PanelState;

extern PanelState *data_ov015_0207e960;

extern PanelElement *FindWidgetById(void *panel, int elementId);
extern void func_ov027_020b9380(void *panel, PanelElement *element, ElementPos *pos, int flag);
extern void func_ov027_020b91e8(void *panel, PanelElement *element, ElementPos *pos, int flag);
extern void SetEntrySlotsVisible(void *panel, PanelElement *element, BOOL visible);

void BlinkPanelCursor(void)
{
    ElementPos pos;
    PanelElement *element;
    u8 *panel;

    panel = data_ov015_0207e960->panel;
    if (data_ov015_0207e960->screenMode == 2) {
        panel = data_ov015_0207e960->subPanel;
    }
    func_ov027_020b9380(panel, FindWidgetById(panel, 8), &pos, 0);
    pos.x += 0x1000;
    func_ov027_020b91e8(panel, FindWidgetById(panel, 8), &pos, 0);
    data_ov015_0207e960->blinkTimer++;
    if (data_ov015_0207e960->blinkTimer > 15) {
        element = FindWidgetById(panel, 8);
        if (element != NULL && element->visible) {
            SetEntrySlotsVisible(panel, element, FALSE);
        } else {
            SetEntrySlotsVisible(panel, element, TRUE);
        }
        data_ov015_0207e960->blinkTimer = 0;
    }
}
