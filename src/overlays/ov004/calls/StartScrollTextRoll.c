#include "nitro/types.h"

#define reg_GX_DISPCNT     (*(volatile u32 *)0x04000000)
#define reg_GXS_DB_DISPCNT (*(volatile u32 *)0x04001000)
#define reg_G2_BLDCNT      (*(volatile u16 *)0x04000050)
#define reg_G2S_DB_BLDCNT  (*(volatile u16 *)0x04001050)

typedef struct {
    s16 x;
    s16 y;
} ScrollOffset;

typedef struct {
    u32 unk_00;
    u8 pad_04[4];
    u32 unk_08;
    u8 pad_0c[0x10916 - 0xc];
    u16 pendingDrop;
    u8 pad_10918[0x1092d - 0x10918];
    u8 state;
    u8 subState;
    u8 pad_1092f;
    ScrollOffset scroll;
    ScrollOffset prevScroll;
    s32 scrollSpeed;
    s32 scrollDelta;
} ScrollScreen;

typedef struct {
    u8 pad_00[4];
    s32 mode;
    u8 pad_08[0x14 - 0x8];
    ScrollScreen screens[2];
    u8 pad_21294[0x23294 - 0x21294];
    u8 commandBuffer[0x800];
    u8 pad_23a94[0x23ac1 - 0x23a94];
    u8 rolling : 1;
    u8 pad_23ac2[0x23acc - 0x23ac2];
    u16 lineIndex;
    u16 lineDelay;
    void *script;
} ScrollTextWork;

typedef struct {
    u32 frameCount;
    ScrollTextWork *work;
} ScrollTextGlobals;

extern ScrollTextGlobals data_ov004_020645a0;
extern u8 data_ov004_02063ec0[];
extern char sOv004_SfV_02064578[];

extern void ApplyScrollTextOffsets(void);
extern int NNS_GfdRegisterNewVramTransferTask(void *command, int offset, void *data, int size);
extern void G2x_SetBlendBrightness_(u32 regAddr, int plane, int brightness);
extern void InvokeForChannelOrBoth(u32 irqMask, const char *name, void (*callback)(void), int channel);

void StartScrollTextRoll(void)
{
    ScrollTextWork *work = data_ov004_020645a0.work;
    ScrollScreen *mainScreen;
    ScrollScreen *subScreen;

    work->mode = 1;
    data_ov004_020645a0.work->script = data_ov004_02063ec0;
    data_ov004_020645a0.work->lineDelay = 100;
    data_ov004_020645a0.work->lineIndex = 0;
    mainScreen = &work->screens[0];
    mainScreen->unk_00 = mainScreen->unk_08;
    subScreen = &work->screens[1];
    subScreen->unk_00 = subScreen->unk_08;
    NNS_GfdRegisterNewVramTransferTask((void *)0xa, 0, data_ov004_020645a0.work->commandBuffer, 0x800);
    NNS_GfdRegisterNewVramTransferTask((void *)0x1a, 0, data_ov004_020645a0.work->commandBuffer, 0x800);
    reg_GX_DISPCNT = (reg_GX_DISPCNT & ~0x1f00) | 0x1700;
    reg_GXS_DB_DISPCNT = (reg_GXS_DB_DISPCNT & ~0x1f00) | 0x1700;
    reg_GX_DISPCNT = (reg_GX_DISPCNT & ~0xe000) | 0x2000;
    reg_GXS_DB_DISPCNT = (reg_GXS_DB_DISPCNT & ~0xe000) | 0x2000;
    reg_G2_BLDCNT = 0;
    reg_G2S_DB_BLDCNT = 0;
    mainScreen->subState = 0;
    subScreen->subState = 0;
    mainScreen->state = 5;
    subScreen->state = 5;
    G2x_SetBlendBrightness_(0x04000050, 4, -16);
    G2x_SetBlendBrightness_(0x04001050, 4, -16);
    InvokeForChannelOrBoth(1, sOv004_SfV_02064578, ApplyScrollTextOffsets, 0);
    mainScreen->pendingDrop = 0;
    subScreen->pendingDrop = 0;
    mainScreen->scrollSpeed = 0xf0000;
    subScreen->scrollSpeed = 0;
    mainScreen->scrollDelta = 0;
    subScreen->scrollDelta = 0;
    data_ov004_020645a0.work->rolling = 1;
}
