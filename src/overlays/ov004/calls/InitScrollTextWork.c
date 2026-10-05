#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x18];
    s32 scrollPosition;
    u8 pad_1c[0x1092c - 0x1c];
    s8 brightness;
    u8 pad_1092d[2];
    u8 subState;
    u8 pad_10930[0x10940 - 0x10930];
} ScrollScreen;

typedef struct {
    u8 pad_00[4];
    s32 mode;
    u8 pad_08[0x14 - 0x8];
    ScrollScreen screens[2];
    u8 pad_21294[0x23ac4 - 0x21294];
    u32 unk_23ac4_0 : 2;
    u32 lidClosed : 1;
    u32 unk_23ac4_3 : 29;
    s32 unk_23ac8;
    u8 pad_23acc[0x30350 - 0x23acc];
    u32 unk_30350_0 : 1;
    u32 unk_30350_1 : 1;
} ScrollTextWork;

typedef struct {
    u32 frameCount;
    ScrollTextWork *work;
} ScrollTextGlobals;

extern ScrollTextGlobals data_ov004_020645a0;

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void LoadScrollTextResources(void);

void *InitScrollTextWork(void)
{
    ScrollTextWork *work = NNSi_FndGetCurrentRootHeap();

    data_ov004_020645a0.work = work;
    work->lidClosed = ((*(volatile u16 *)0x02ffffa8 & 0x8000) >> 15) != 0;
    data_ov004_020645a0.work->screens[0].subState = 0;
    data_ov004_020645a0.work->screens[1].subState = 0;
    data_ov004_020645a0.work->screens[0].brightness = -16;
    data_ov004_020645a0.work->screens[1].brightness = -16;
    data_ov004_020645a0.work->mode = 0;
    data_ov004_020645a0.work->screens[0].scrollPosition = 0;
    data_ov004_020645a0.work->screens[1].scrollPosition = 0;
    data_ov004_020645a0.work->unk_23ac8 = 0;
    data_ov004_020645a0.work->unk_30350_0 = 0;
    data_ov004_020645a0.work->unk_30350_1 = 0;
    return LoadScrollTextResources;
}
