#include "nitro/types.h"

typedef struct NNSFndList {
    void *headObject;
    void *tailObject;
    u16 numObjects;
    u16 offset;
} NNSFndList;

extern NNSFndList *data_ov027_020ba3e4;
extern void *NNS_FndGetNextListObject(void *list, void *obj);

BOOL IsFileLoadQueueEmpty(void)
{
    NNSFndList *queue = data_ov027_020ba3e4;
    BOOL empty;

    if (queue == NULL) {
        return FALSE;
    }
    empty = FALSE;
    if (NNS_FndGetNextListObject(queue, NULL) == NULL) {
        empty = TRUE;
    }
    return empty;
}
