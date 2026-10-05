#include "nitro/types.h"

typedef struct Tween {
    int duration;
    int mode;
    int start;
    int end;
    u8 pad_10[0xC];
} Tween;

typedef struct Widget {
    u8 pad_00[0x5C];
    Tween tweenX;
    Tween tweenY;
} Widget;

extern void func_ov027_020b9380(void *root, Widget *widget, int *pos, int flags);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void func_02052528(Tween *tween, int duration, int start, int end, int mode);
extern void func_02052570(Tween *tween);

void StartWidgetMoveTween(void *root, Widget *widget, int duration, const int *from, const int *to, int mode)
{
    int pos[2];

    if (from == NULL) {
        func_ov027_020b9380(root, widget, pos, 0);
    } else {
        MI_CpuCopy8(from, pos, 8);
    }
    func_02052528(&widget->tweenX, duration, pos[0], to[0], mode);
    func_02052528(&widget->tweenY, duration, pos[1], to[1], mode);
    func_02052570(&widget->tweenX);
    func_02052570(&widget->tweenY);
}
