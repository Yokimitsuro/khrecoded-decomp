#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct PanelElement PanelElement;

typedef struct ElementPos {
    fx32 x;
    fx32 y;
} ElementPos;

typedef struct PanelState {
    u8 pad_00[2];
    s8 page;
    u8 pad_03[0x6abd];
    u8 panel[1];
} PanelState;

extern PanelState *data_ov015_0207e960;

extern PanelElement *FindWidgetById(void *panel, int elementId);
extern void func_ov027_020b96c0(void *panel, PanelElement *element, int mode);
extern void func_ov027_020b9380(void *panel, PanelElement *element, ElementPos *pos, int flag);
extern void func_ov027_020b91e8(void *panel, PanelElement *element, ElementPos *pos, int flag);
extern void SetFocusedWidget(void *panel, PanelElement *element);
extern BOOL PlaySoundEffect(int seqArcNo, int index);

void SelectNextPanelPage(void)
{
    ElementPos pos;
    PanelState *state;
    u8 *panel;

    data_ov015_0207e960->page++;
    if (data_ov015_0207e960->page >= 6) {
        data_ov015_0207e960->page = 0;
    }
    state = data_ov015_0207e960;
    panel = state->panel;
    func_ov027_020b96c0(panel, FindWidgetById(panel, 10), state->page);
    panel = data_ov015_0207e960->panel;
    func_ov027_020b9380(panel, FindWidgetById(panel, 10), &pos, 0);
    pos.x -= 0x19000;
    panel = data_ov015_0207e960->panel;
    func_ov027_020b91e8(panel, FindWidgetById(panel, 11), &pos, 0);
    panel = data_ov015_0207e960->panel;
    SetFocusedWidget(panel, FindWidgetById(panel, 10));
    PlaySoundEffect(2, 1);
}
