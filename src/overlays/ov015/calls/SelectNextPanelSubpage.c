#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct PanelElement PanelElement;

typedef struct ElementPos {
    fx32 x;
    fx32 y;
} ElementPos;

typedef struct PanelState {
    u8 pad_00[3];
    s8 subpage;
    u8 pad_04[0x6abc];
    u8 panel[1];
} PanelState;

extern PanelState *data_ov015_0207e960;
extern int data_ov015_0207a19c[];

extern u32 DispatchContextCommand(u32 command, u32 value, u32 extra, void *buffer);
extern void DrawPanelInfoText(void);
extern PanelElement *FindWidgetById(void *panel, int elementId);
extern void func_ov027_020b9380(void *panel, PanelElement *element, ElementPos *pos, int flag);
extern void func_ov027_020b91e8(void *panel, PanelElement *element, ElementPos *pos, int flag);
extern void SetFocusedWidget(void *panel, PanelElement *element);
extern BOOL PlaySoundEffect(int seqArcNo, int index);

void SelectNextPanelSubpage(void)
{
    ElementPos pos;
    PanelState *state;
    u8 *panel;

    data_ov015_0207e960->subpage++;
    state = data_ov015_0207e960;
    if (state->subpage >= data_ov015_0207a19c[DispatchContextCommand(6, 0, 0, NULL)]) {
        state->subpage = 0;
    }
    DrawPanelInfoText();
    panel = data_ov015_0207e960->panel;
    func_ov027_020b9380(panel, FindWidgetById(panel, 4), &pos, 0);
    pos.x -= 0x34000;
    pos.y -= 0x19000;
    panel = data_ov015_0207e960->panel;
    func_ov027_020b91e8(panel, FindWidgetById(panel, 11), &pos, 0);
    panel = data_ov015_0207e960->panel;
    SetFocusedWidget(panel, FindWidgetById(panel, 4));
    PlaySoundEffect(2, 1);
}
