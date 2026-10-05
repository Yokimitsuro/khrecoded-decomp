#include "nitro/types.h"

#define reg_GX_DISPCNT     (*(volatile u32 *)0x04000000)
#define reg_GXS_DB_DISPCNT (*(volatile u32 *)0x04001000)

typedef struct {
    u16 startFrame;
    u16 endFrame;
} FrameTimer;

typedef struct {
    u8 pad_00[4];
    s32 mode;
    u8 pad_08[0x30344 - 0x8];
    FrameTimer exitTimer;
} ScrollTextWork;

typedef struct {
    u32 frameCount;
    ScrollTextWork *work;
} ScrollTextGlobals;

extern ScrollTextGlobals data_ov004_020645a0;
extern char sOv004_SfV_02064578[];

extern void NotifyBothOrOne(u32 irqMask, const char *name, int channel);
extern void FrameTimer_Start(FrameTimer *timer, int duration);
extern void StopSoundStreamAtIndex(int handleIndex, int fadeFrame);

void BeginScrollTextExit(void)
{
    NotifyBothOrOne(1, sOv004_SfV_02064578, 0);
    data_ov004_020645a0.work->mode = 2;
    FrameTimer_Start(&data_ov004_020645a0.work->exitTimer, 0x1e);
    reg_GX_DISPCNT = (reg_GX_DISPCNT & ~0x1f00) | 0x1500;
    reg_GXS_DB_DISPCNT = (reg_GXS_DB_DISPCNT & ~0x1f00) | 0x1100;
    StopSoundStreamAtIndex(0, 0x1e);
}
