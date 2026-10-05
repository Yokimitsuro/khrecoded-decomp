#include "nitro/types.h"

extern u8 *data_0206084c;
extern void *data_02060394;
extern void *NNSi_FndAllocFromExpHeapEx(u32 size, void *heap);
extern void MI_CpuFill8(void *dest, u32 value, u32 size);
extern void NNS_SndInit(void);
extern u32 NNS_SndHeapCreate(void *buffer, u32 size);
extern void func_0204cacc(void);

BOOL InitSoundSystem(void)
{
    u8 *scene;

    if (data_0206084c != NULL) {
        return TRUE;
    }
    scene = NNSi_FndAllocFromExpHeapEx(0xb47dc, data_02060394);
    data_0206084c = scene;
    MI_CpuFill8(scene, 0, 0xb47dc);
    NNS_SndInit();
    *(u32 *)(scene + 0xb04b4) = NNS_SndHeapCreate(scene + 0xb4, 0x65400);
    *(u32 *)(scene + 0xb04b8) = NNS_SndHeapCreate(scene + 0x654b4, 0x4b000);
    *(u32 *)(scene + 0xb44bc) = NNS_SndHeapCreate(scene + 0xb04bc, 0x4000);
    func_0204cacc();
    *(u32 *)(scene + 0xb4500) = 0;
    *(u32 *)(scene + 0xb4504) = 0;
    *(u32 *)(scene + 0xb4508) = 0;
    *(u32 *)(scene + 0xb450c) = 0x1000;
    *(u32 *)(scene + 0xb4510) = 0;
    *(u32 *)(scene + 0xb4514) = 0;
    scene[0xb47be] = 0;
    scene[0xb47d3] = 0;
    scene[0xb47d2] = 0;
    scene[0xb472e] = 0;
    scene[0xb472f] = 0x7f;
    scene[0xb47be] = 0;
    *(u32 *)(scene + 0xb4720) = 0xa000;
    *(u32 *)(scene + 0xb4724) = 0x32000;
    *(u16 *)(scene + 0xb4728) = 0x7f;
    scene[0xb47d4] = 0;
    scene[0xb47d5] = 1;
    *(s16 *)(scene + 0xb4736) = -1;
    *(u16 *)(scene + 0xb4734) = 0;
    *(u16 *)(scene + 0xb47d6) = 0x7f;
    return TRUE;
}
