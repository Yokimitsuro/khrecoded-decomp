#include "nitro/types.h"

extern void MI_CpuFill8(void *dest, u32 value, u32 size);
extern u32 gSoundCategoryNames[];
extern char sMain_BaChFormatSWpBZ_02056178[];
extern void *OS_SPrintf(char *dst, const char *fmt, ...);
extern void *func_0202c4a0(void *buffer, u32 code);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void PackNamedRecordEntry(u8 *out, int index, int nameId, u32 extra)
{
    char buffer[128];
    u32 unused;
    u32 recordBase;
    u32 record;

    unused = extra;
    MI_CpuFill8(out, 0, 0x1c);
    OS_SPrintf(buffer, sMain_BaChFormatSWpBZ_02056178, gSoundCategoryNames[nameId]);
    recordBase = (u32)func_0202c4a0(buffer, 0x11);
    out[0] = (u8)index;
    record = recordBase + index * 0x24;
    out[1] = (u8)*(u32 *)record;
    out[2] = (u8)*(u32 *)(record + 4);
    *(u16 *)(out + 0xc) = (u16)*(u32 *)(record + 8);
    *(u16 *)(out + 4) = (u16)*(u32 *)(record + 0xc);
    *(u32 *)(out + 8) = *(u32 *)(record + 0x10);
    out[0x18] = (u8)*(u32 *)(record + 0x14);
    out[0x19] = (u8)*(u32 *)(record + 0x18);
    out[0x1a] = (u8)*(u32 *)(record + 0x1c);
    out[0x1b] = (u8)*(u32 *)(record + 0x20);
    NNSi_FndFreeFromDefaultHeap((void *)recordBase);
}
