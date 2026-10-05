#include "nitro/types.h"

typedef struct Tween Tween;

typedef struct MessageWindow {
    int layer;
    u8 pad_04[4];
    int state;
    u8 pad_0c[0x10];
    u8 tween[0x18];
    u32 unk34_0 : 2;
    u32 opening : 1;
    u32 unk34_3 : 29;
    u8 pad_38[0x10];
    s32 closeTimer;
    u8 pad_4c[0x38];
    u32 tickLo;
    u32 tickHi;
} MessageWindow;

extern s32 *data_ov001_020a04e4;
extern int func_ov001_0207123c(void);
extern int func_ov027_020b9e10(int widgets, int layer);
extern void func_ov027_020b9e20(int widgets, int layer);
extern void SampleTweenValue(Tween *tween, s32 *out);
extern void DrawScaledWindowFrame(MessageWindow *window, int target, int percent);
extern void func_ov001_020794c8(MessageWindow *window);
extern void DrawWindowScrollArrow(MessageWindow *window);
extern u64 OS_GetTick(void);

void UpdateTweenedMessageWindow(MessageWindow *window)
{
    int widgets = func_ov001_0207123c();
    int target = func_ov027_020b9e10(widgets, 11);
    s32 *mode = data_ov001_020a04e4;
    s32 percent;

    SampleTweenValue((Tween *)window->tween, &percent);
    DrawScaledWindowFrame(window, target, percent);
    if (window->opening) {
        func_ov001_020794c8(window);
        if ((window->closeTimer != 0x7fffffff && *mode == 8) || *mode == 9) {
            DrawWindowScrollArrow(window);
        }
        *(u64 *)&window->tickLo = OS_GetTick();
        window->state = 4;
    }
    func_ov027_020b9e20(widgets, 11);
}
