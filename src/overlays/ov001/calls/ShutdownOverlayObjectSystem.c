#include "nitro/types.h"

typedef struct ActorManager {
    u8 pad_000[0x140];
    u8 pad_140[0x3DA4];
    void *heapHandle;
    void *rootObject;
} ActorManager;

extern ActorManager *data_ov001_020a0500;
extern void func_020257f8(void *dst);
extern void StoreGlobalArrayEntry(int index, void *value);
extern void PXI_Init_0202a64c(void *arg0);

void ShutdownOverlayObjectSystem(void)
{
    ActorManager *manager;

    manager = data_ov001_020a0500;
    func_020257f8((u8 *)data_ov001_020a0500 + 0x140);
    StoreGlobalArrayEntry(1, 0);
    PXI_Init_0202a64c(manager->rootObject);
    data_ov001_020a0500 = 0;
}
