#include "nitro/types.h"

typedef struct PanelPos {
    s32 x;
    s32 y;
} PanelPos;

typedef struct Widget {
    u8 pad_00[0xc];
    int kind;
} Widget;

typedef struct PanelState {
    u8 pad_0000[0xe0];
    u8 flags;
    u8 pad_00e1[0xec - 0xe1];
    int selectedKind;
    u8 pad_00f0[0x6ac0 - 0xf0];
    u8 container[4];
} PanelState;

extern PanelState *data_ov015_0207e960;
extern void ClearContextFlagBit(int index);
extern void func_ov027_020b9380(void *container, Widget *widget, PanelPos *pos, int flag);
extern void StartWidgetMoveTween(void *container, Widget *widget, int mode, PanelPos *from,
                                          PanelPos *to, int duration);
extern BOOL PlaySoundEffect(int seqArcNo, int index);

void SelectWidgetAndSlideOut(Widget *widget)
{
    PanelPos pos;
    PanelPos target;

    switch (widget->kind) {
    case 1:
        data_ov015_0207e960->selectedKind = 0;
        ClearContextFlagBit(0);
        break;
    case 2:
        data_ov015_0207e960->selectedKind = 1;
        ClearContextFlagBit(1);
        break;
    case 3:
        data_ov015_0207e960->selectedKind = 2;
        ClearContextFlagBit(2);
        break;
    }
    func_ov027_020b9380(data_ov015_0207e960->container, widget, &pos, 0);
    target = pos;
    target.y = -0x64000;
    StartWidgetMoveTween(data_ov015_0207e960->container, widget, 1, &pos, &target, 1000);
    PlaySoundEffect(2, 8);
    data_ov015_0207e960->flags |= 0x40;
}
