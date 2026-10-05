#include "nitro/types.h"

typedef struct {
    u16 field0;
    u16 field2;
    void *field4;
    void *field8;
    u32 fieldC;
} Record;

extern Record *FindRecordById(u32 id);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void *NNS_FndAllocFromDefaultExpHeapEx(u32 size, int align);
extern void MI_CpuCopy8(void *src, void *dst, u32 size);

/* Clones a record and its two sub-blocks. */
Record *CloneRecord(Record **out, u32 id, int useTailAlloc)
{
    Record *clone;
    Record *source;
    void *block;
    int entryBase;
    u8 *payload;
    int i;

    source = FindRecordById(id);
    if (source == NULL) {
        return NULL;
    }
    if (useTailAlloc != 0) {
        clone = NNS_FndAllocFromDefaultExpHeapEx(0x10, -4);
        block = NNS_FndAllocFromDefaultExpHeapEx(*(u32 *)source->field4, -4);
        clone->field4 = block;
        block = NNS_FndAllocFromDefaultExpHeapEx(*(u32 *)source->field8, -4);
    } else {
        clone = NNSi_FndAllocFromDefaultHeap(0x10);
        block = NNSi_FndAllocFromDefaultHeap(*(u32 *)source->field4);
        clone->field4 = block;
        block = NNSi_FndAllocFromDefaultHeap(*(u32 *)source->field8);
    }
    clone->field8 = block;
    clone->field0 = source->field0;
    clone->field2 = source->field2;
    clone->fieldC = source->fieldC;
    MI_CpuCopy8(source->field4, clone->field4, *(u32 *)source->field4);
    MI_CpuCopy8(source->field8, clone->field8, *(u32 *)source->field8);

    entryBase = (int)clone->field8;
    payload = (u8 *)(entryBase + 8 + *(u16 *)(entryBase + 6) * 4);
    for (i = 0; i < *(u16 *)(entryBase + 6); i++) {
        *(u8 **)(entryBase + i * 4 + 8) = payload;
        payload = payload + *(u32 *)payload;
    }
    *out = clone;
    return clone;
}
