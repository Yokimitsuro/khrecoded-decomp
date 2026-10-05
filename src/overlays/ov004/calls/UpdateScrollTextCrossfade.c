#include "nitro/types.h"

typedef struct {
    u16 startFrame;
    u16 endFrame;
} FrameTimer;

typedef struct {
    u8 pad_00[0x10924];
    FrameTimer fadeTimer;
    u8 pad_10928[0x1092d - 0x10928];
    u8 state;
    u8 subState;
    u8 pad_1092f[0x10940 - 0x1092f];
} ScrollScreen;

typedef struct {
    u8 pad_00[0x14];
    ScrollScreen screens[2];
    u8 pad_21294[0x23ac1 - 0x21294];
    u8 rolling : 1;
} ScrollTextWork;

typedef struct {
    u32 frameCount;
    ScrollTextWork *work;
} ScrollTextGlobals;

extern ScrollTextGlobals data_ov004_020645a0;

extern int FrameTimer_Interpolate(FrameTimer *timer, int scale);
extern void G2x_SetBlendAlpha_(u32 regAddr, int plane1, int plane2, int ev1, int ev2);

void UpdateScrollTextCrossfade(void)
{
    int blend[2];
    int fadeIn;
    int fadeOut;

    switch (data_ov004_020645a0.work->screens[0].state) {
    case 3:
        fadeIn = FrameTimer_Interpolate(&data_ov004_020645a0.work->screens[data_ov004_020645a0.work->rolling ^ 1].fadeTimer, 0x10);
        fadeOut = FrameTimer_Interpolate(&data_ov004_020645a0.work->screens[data_ov004_020645a0.work->rolling].fadeTimer, 0x10);
        blend[0] = 0x10 - fadeOut;
        blend[1] = fadeIn;
        G2x_SetBlendAlpha_(0x04000050, 4, 0x28, blend[data_ov004_020645a0.work->rolling], blend[data_ov004_020645a0.work->rolling ^ 1]);
        G2x_SetBlendAlpha_(0x04001050, 4, 0x28, blend[data_ov004_020645a0.work->rolling], blend[data_ov004_020645a0.work->rolling ^ 1]);
        if (fadeIn == 0x10 && fadeOut == 0x10) {
            data_ov004_020645a0.work->screens[0].subState = 0;
            data_ov004_020645a0.work->screens[1].subState = 0;
            data_ov004_020645a0.work->screens[0].state = 5;
            data_ov004_020645a0.work->screens[1].state = 5;
        }
        break;
    case 4:
        fadeOut = FrameTimer_Interpolate(&data_ov004_020645a0.work->screens[data_ov004_020645a0.work->rolling].fadeTimer, 0x10);
        blend[0] = 0x10 - fadeOut;
        blend[1] = 0;
        G2x_SetBlendAlpha_(0x04000050, 4, 0x28, blend[data_ov004_020645a0.work->rolling], blend[data_ov004_020645a0.work->rolling ^ 1]);
        G2x_SetBlendAlpha_(0x04001050, 4, 0x28, blend[data_ov004_020645a0.work->rolling], blend[data_ov004_020645a0.work->rolling ^ 1]);
        break;
    }
}
