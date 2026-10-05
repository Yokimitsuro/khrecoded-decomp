#include "nitro/types.h"

struct NNSiFndHeapHead;
extern void *OS_AllocFromArenaLo(int arena, u32 size, u32 align);
extern struct NNSiFndHeapHead *NNS_FndCreateExpHeapEx(void *startAddress, u32 size, u16 optionFlag);
extern u32 OS_GetArenaHi(int index);
extern u32 OS_GetArenaLo(int index);

void CreateEngineHeaps(void **specialHeapOut, void **defaultHeapOut)
{
    void *specialHeap = OS_AllocFromArenaLo(0, 0xc2800, 0x10);
    specialHeap = NNS_FndCreateExpHeapEx(specialHeap, 0xc2800, 0);
    u32 tableB = OS_GetArenaLo(0);
    u32 tableA = OS_GetArenaHi(0);
    u32 defaultSize = (tableA & 0xfffffff0) - ((tableB + 0xf) & 0xfffffff0);
    void *defaultHeap = OS_AllocFromArenaLo(0, defaultSize, 0x10);
    defaultHeap = NNS_FndCreateExpHeapEx(defaultHeap, defaultSize, 0);
    *specialHeapOut = specialHeap;
    *defaultHeapOut = defaultHeap;
}
