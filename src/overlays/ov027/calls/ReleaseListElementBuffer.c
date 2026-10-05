#include "nitro/types.h"

typedef struct ListElement {
    u8 pad_00[0x24];
    u8 active : 1;
    u8 loaded : 1;
    u8 pad_25[7];
    void *buffer;
} ListElement;

extern void NNSi_FndFreeFromDefaultHeap(void *block);

void ReleaseListElementBuffer(void *list, ListElement *element)
{
    element->loaded = 0;
    if (element->buffer != NULL) {
        NNSi_FndFreeFromDefaultHeap(element->buffer);
        element->buffer = NULL;
    }
}
