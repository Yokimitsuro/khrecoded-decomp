#include "nitro/types.h"

extern void DestroyFndObjectList(void *list);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);

void DestroyOwnedObjectList(void **listRef)
{
    if (listRef != NULL && *listRef != NULL) {
        DestroyFndObjectList(*listRef);
        if (*listRef != NULL) {
            NNSi_FndFreeFromDefaultHeap(*listRef);
            *listRef = NULL;
        }
    }
}
