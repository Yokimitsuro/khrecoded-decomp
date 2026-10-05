#include "nitro/types.h"

typedef struct NNSFndList {
    void *headObject;
    void *tailObject;
    u16 numObjects;
    u16 offset;
} NNSFndList;

extern void *NNS_FndGetNextListObject(NNSFndList *list, void *object);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);

BOOL DestroyFndObjectList(int container) {
    NNSFndList *list;
    void *object;
    void *next;

    list = (NNSFndList *)(container + 4);
    object = NNS_FndGetNextListObject(list, 0);
    while (object != 0) {
        next = NNS_FndGetNextListObject(list, object);
        NNSi_FndFreeFromDefaultHeap(*(void **)((u32)object + 0x24));
        NNSi_FndFreeFromDefaultHeap(object);
        object = next;
    }
    return 1;
}
