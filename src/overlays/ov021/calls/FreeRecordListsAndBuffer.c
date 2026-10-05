#include "nitro/types.h"

extern void NNSi_FndFreeFromDefaultHeap(void *block);

typedef struct {
    s32 count0;
    u8 *list0;
    s32 count1;
    u8 *list1;
    void *single;
} RecordLists;

void FreeRecordListsAndBuffer(RecordLists *obj)
{
    s32 i;

    if (obj->single != 0) {
        NNSi_FndFreeFromDefaultHeap(obj->single);
        obj->single = 0;
    }
    if (obj->list1 != 0) {
        for (i = 0; i < obj->count1; i++) {
            void *sub = *(void **)(obj->list1 + i * 0x10 + 8);
            if (sub != 0) {
                NNSi_FndFreeFromDefaultHeap(sub);
            }
        }
        NNSi_FndFreeFromDefaultHeap(obj->list1);
        obj->list1 = 0;
        obj->count1 = 0;
    }
    if (obj->list0 != 0) {
        for (i = 0; i < obj->count0; i++) {
            NNSi_FndFreeFromDefaultHeap(*(void **)(obj->list0 + i * 8 + 4));
        }
        NNSi_FndFreeFromDefaultHeap(obj->list0);
        obj->list0 = 0;
        obj->count0 = 0;
    }
}
