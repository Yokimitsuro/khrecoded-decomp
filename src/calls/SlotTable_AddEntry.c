#include "nitro/types.h"

extern void MIi_CpuClear32(u32 data, void *dst, u32 size);
extern int FindFreeRecordSlot(void *table);
extern void func_0204e564(void *dst, u32 a, void *b, int c);
extern void *GetElementAddress(void *table, int index);
extern void AppendDoubleLinkedNode(void *list, void *node);

int SlotTable_AddEntry(void *table, int animIndex, int bankIndex)
{
    int index;
    char *entry;
    char *bank;

    index = FindFreeRecordSlot(table);
    entry = (char *)table + 4 + index * 0x8c;

    *(u32 *)(entry + 0x78) &= ~1u;
    *(u32 *)(entry + 0x78) |= 7u;
    *(u32 *)(entry + 0x78) &= ~8u;
    *(u32 *)(entry + 0x78) &= ~0x10u;
    *(u32 *)(entry + 0x78) &= ~0x20u;
    *(u32 *)(entry + 0x7c) = 0x1000;
    *(u32 *)(entry + 0x80) = 0;
    *(u32 *)(entry + 0x84) = 0x1000;
    *(u32 *)(entry + 0x88) = 0x1000;
    *(u32 *)(entry + 0x70) = 0;
    *(int *)(entry + 0x74) = bankIndex;

    MIi_CpuClear32(0, entry + 0xc, 8);

    bank = (char *)GetElementAddress(table, bankIndex);
    func_0204e564(entry + 0x14, *(u32 *)(bank + 0x14), *(void **)(bank + 0x10), animIndex);

    *(int *)(entry + 0x6c) = *(s16 *)(bank + 0x64);
    AppendDoubleLinkedNode(table, entry);
    return index;
}
