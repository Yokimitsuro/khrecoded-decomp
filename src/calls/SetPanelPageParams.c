#include "nitro/types.h"

extern void func_0202845c(int base, s32 index);

void SetPanelPageParams(int base, s32 index, u32 valueA, s32 valueB, u32 valueC, u32 valueD, u32 valueE, u32 valueF)
{
    int entry = base + index * 0x18;

    *(u32 *)(entry + 0x10) = valueA;
    *(s32 *)(entry + 0x14) = valueB << 1;
    *(u32 *)(entry + 0x18) = valueC;
    *(u32 *)(entry + 0x1c) = valueD;
    *(u32 *)(entry + 0x20) = valueE;
    *(u32 *)(entry + 0x24) = valueF;
    func_0202845c(base, index);
}
