#include "nitro/types.h"

typedef struct {
    u16 startFrame;
    u16 endFrame;
} FrameTimer;

typedef struct {
    s32 waitFrames;
    s32 mode;
    s32 prevMode;
    u8 pad_0c[0x23ac4 - 0xc];
    int unk_bit0 : 1;
    int waitInput : 1;
    s32 skippable;
    u16 lineIndex;
    u16 lineCount;
    u8 pad_23ad0[0x30344 - 0x23ad0];
    FrameTimer exitTimer;
    FrameTimer lineTimer;
} ScrollTextWork;

typedef struct {
    u32 frameCount;
    ScrollTextWork *work;
} ScrollTextGlobals;

extern ScrollTextGlobals data_ov004_020645a0;
extern void (*gScrollTextHandlers[])(void);
extern u16 data_02060500;

extern void func_ov004_020619a0(void);
extern BOOL FrameTimer_IsExpired(FrameTimer *timer);
extern void StartScrollTextRoll(void);
extern void BeginScrollTextExit(void);
extern void FrameTimer_Start(FrameTimer *timer, int duration);
extern void StopSoundStreamAtIndex(int handleIndex, int fadeFrame);

int RunScrollTextFrame(void)
{
    s32 mode;
    int done;

    gScrollTextHandlers[data_ov004_020645a0.work->mode]();
    mode = data_ov004_020645a0.work->mode;
    if (mode == 3) {
        return 0;
    }
    if (mode == 4) {
        return -2;
    }
    if (mode < 2) {
        if (!data_ov004_020645a0.work->waitInput) {
            func_ov004_020619a0();
            if (!data_ov004_020645a0.work->waitInput &&
                FrameTimer_IsExpired(&data_ov004_020645a0.work->lineTimer) &&
                data_ov004_020645a0.work->lineIndex == data_ov004_020645a0.work->lineCount) {
                switch (data_ov004_020645a0.work->mode) {
                case 0:
                    StartScrollTextRoll();
                    break;
                case 1:
                    BeginScrollTextExit();
                    break;
                }
            }
        } else {
            if (data_ov004_020645a0.work->skippable == 0) {
                done = data_02060500 & 1;
            } else {
                data_ov004_020645a0.work->waitFrames++;
                done = data_ov004_020645a0.work->waitFrames >= 180;
            }
            if (done) {
                data_ov004_020645a0.work->waitInput = 0;
            }
        }
        if (data_ov004_020645a0.work->skippable != 0 && (data_02060500 & 8)) {
            data_ov004_020645a0.work->prevMode = data_ov004_020645a0.work->mode;
            data_ov004_020645a0.work->mode = 2;
            FrameTimer_Start(&data_ov004_020645a0.work->exitTimer, 30);
            StopSoundStreamAtIndex(0, 30);
        }
    }
    data_ov004_020645a0.frameCount++;
    return 0;
}
