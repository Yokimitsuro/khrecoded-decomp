#include "nitro/types.h"

typedef struct PanelWork {
    u8 pad_0000[0x14];
    int mode;
    u8 pad_0018[0x148];
    u8 panel[1];
} PanelWork;

extern PanelWork *data_ov015_020812e0;

extern void *FindWidgetById(void *panel, int slot);
extern void SetFocusedWidget(void *panel, void *entry);
extern void SetWidgetRootDpadEnabled(void *panel, int value);
extern void SetWidgetRootTouchEnabled(void *panel, int value);
extern void func_ov015_020779a4(int a, int b);
extern BOOL PlaySoundEffect(int seqArcNo, int index);

void OnPanelSlot17Selected(void)
{
    SetFocusedWidget(data_ov015_020812e0->panel, FindWidgetById(data_ov015_020812e0->panel, 0x11));
    SetWidgetRootDpadEnabled(data_ov015_020812e0->panel, 0);
    SetWidgetRootTouchEnabled(data_ov015_020812e0->panel, 0);
    data_ov015_020812e0->mode = 4;
    func_ov015_020779a4(0x24, 0x23);
    PlaySoundEffect(2, 1);
}
