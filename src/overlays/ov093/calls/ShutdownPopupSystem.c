#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x1c];
    void *resourceFile;
} PopupWork;

extern PopupWork *data_ov093_020c5104;
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void ShutdownPopupSystem(void)
{
    if (data_ov093_020c5104->resourceFile != NULL) {
        NNSi_FndFreeFromDefaultHeap(data_ov093_020c5104->resourceFile);
        data_ov093_020c5104->resourceFile = NULL;
    }
    data_ov093_020c5104 = NULL;
}
