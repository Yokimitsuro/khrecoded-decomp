#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x1c];
    void *fileData;
} PopupManager;

extern PopupManager *data_ov091_020c375c;
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void DestroyPopupManager(void)
{
    if (data_ov091_020c375c->fileData != NULL) {
        NNSi_FndFreeFromDefaultHeap(data_ov091_020c375c->fileData);
        data_ov091_020c375c->fileData = NULL;
    }
    data_ov091_020c375c = NULL;
}
