#include "nitro/types.h"

typedef struct {
    u8 pad_0000[3];
    s8 blinkTimer;
    u8 pad_0004[0x6abc];
    u8 widgets[4];
} PanelContext;

extern PanelContext *data_ov015_0207e960;
extern const int data_ov015_0207a19c[];

extern int DispatchContextCommand(int command, int a, int b, int c);
extern void DrawPanelInfoText(void);
extern void *FindWidgetById(void *widgets, int id);
extern void func_ov027_020b9380(void *widgets, void *widget, int *outPos, int mode);
extern void func_ov027_020b91e8(void *widgets, void *widget, int *pos, int mode);
extern void SetFocusedWidget(void *widgets, void *widget);
extern BOOL PlaySoundEffect(int seqArcNo, int index);

void StepPanelCursorBlink(void) {
    int pos[2];
    void *widgets;

    data_ov015_0207e960->blinkTimer--;
    if (data_ov015_0207e960->blinkTimer < 0) {
        data_ov015_0207e960->blinkTimer = data_ov015_0207a19c[DispatchContextCommand(6, 0, 0, 0)] - 1;
    }
    DrawPanelInfoText();
    widgets = data_ov015_0207e960->widgets;
    func_ov027_020b9380(widgets, FindWidgetById(widgets, 4), pos, 0);
    pos[0] -= 0x34000;
    pos[1] -= 0x19000;
    widgets = data_ov015_0207e960->widgets;
    func_ov027_020b91e8(widgets, FindWidgetById(widgets, 0xb), pos, 0);
    widgets = data_ov015_0207e960->widgets;
    SetFocusedWidget(widgets, FindWidgetById(widgets, 4));
    PlaySoundEffect(2, 1);
}
