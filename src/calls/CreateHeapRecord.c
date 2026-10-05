#include "nitro/types.h"

struct NNSiFndHeapHead;

typedef struct HeapRecord {
    struct NNSiFndHeapHead *heap;
    u32 info[4];
} HeapRecord;

extern struct NNSiFndHeapHead *NNS_FndCreateExpHeapEx(void *startAddress, u32 size, u16 optionFlag);
extern void NNS_FndInitAllocatorForExpHeap(void *dest, struct NNSiFndHeapHead *heap, int count);

HeapRecord *CreateHeapRecord(HeapRecord *record, void *startAddress, u32 size) {
    struct NNSiFndHeapHead *heap = NNS_FndCreateExpHeapEx(startAddress, size, 1);

    if (heap != NULL) {
        record->heap = heap;
        NNS_FndInitAllocatorForExpHeap(record->info, heap, 4);
        return record;
    }
    return NULL;
}
