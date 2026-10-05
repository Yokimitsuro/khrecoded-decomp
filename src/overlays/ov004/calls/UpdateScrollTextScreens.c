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
} ScrollTextWork;

typedef struct {
    u32 frameCount;
    ScrollTextWork *work;
} ScrollTextGlobals;

extern ScrollTextGlobals data_ov004_020645a0;

extern void func_ov004_02062768(void);
extern void func_ov004_020625fc(int screen);

void UpdateScrollTextScreens(void)
{
    switch (data_ov004_020645a0.work->screens[0].state) {
    case 3:
    case 4:
        func_ov004_02062768();
        return;
    }
    func_ov004_020625fc(0);
    func_ov004_020625fc(1);
}
