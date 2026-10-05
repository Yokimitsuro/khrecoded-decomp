#include "nitro/types.h"

typedef struct WindowFade {
    u8 pad_00[0xd8];
    u8 timer[0x1c];
    int active;
} WindowFade;

extern WindowFade *data_ov001_020a04e4;
extern void func_02052528(void *timer, int start, int end, int scale, int duration);
extern void func_02052570(void *timer);

void StartWindow1Fade(int unused, int left, int top, int right, int bottom)
{
    WindowFade *fade = data_ov001_020a04e4;

    *(vu16 *)0x04000042 = (u16)(((left << 8) & 0xff00) | (u8)right);
    *(vu16 *)0x04000046 = (u16)(((top << 8) & 0xff00) | (u8)bottom);
    func_02052528(fade->timer, 0, 0, 0x10000, 1000);
    func_02052570(fade->timer);
    fade->active = 0;
}
