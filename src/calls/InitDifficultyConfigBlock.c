#include "nitro/types.h"

typedef struct {
    u16 field0;
    u16 field2;
    u8 field4;
    u8 pad5[2];
    u8 field7;
    u8 pad8[4];
} ConfigBlock;

extern ConfigBlock data_02060850;
extern void MI_CpuFill8(void *dst, int val, unsigned int n);
extern int ReadGlobalPackedBits(int a, int b);
extern void SetGlobalPackedBit(int bitIndex);

void InitDifficultyConfigBlock(u8 param1)
{
    u32 mode = ReadGlobalPackedBits(0x1a00, 2) & 3;
    if (mode == 3) {
        mode = 0;
    }
    MI_CpuFill8(&data_02060850, 0, 0xc);
    data_02060850.field0 = (u16)ReadGlobalPackedBits(mode * 0xf00 + 0x330b, 10);
    data_02060850.field2 = (u16)ReadGlobalPackedBits(mode * 0xf00 + 0x3315, 10);
    data_02060850.field4 = param1;
    u8 modeByte = (u8)mode;
    data_02060850.field7 = (data_02060850.field7 & ~3) | (modeByte & 3);
    SetGlobalPackedBit(0x1a05);
}
