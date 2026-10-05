#include "nitro/types.h"

typedef struct FieldManager {
    u8 pad_000[0x5d0];
    u8 listeners[0xc];
} FieldManager;

typedef struct FieldManagerHandle {
    BOOL ready;
    FieldManager *manager;
} FieldManagerHandle;

typedef struct FieldListener {
    int value;
    u8 link[0xc];
} FieldListener;

extern FieldManagerHandle data_ov001_020a04c4;
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void NNS_FndAppendListObject(void *list, void *object);

FieldListener *AddFieldListener(int value)
{
    FieldListener *listener;

    data_ov001_020a04c4.ready = FALSE;
    listener = NNSi_FndAllocFromDefaultHeap(sizeof(FieldListener));
    listener->value = value;
    NNS_FndAppendListObject(data_ov001_020a04c4.manager->listeners, listener);
    data_ov001_020a04c4.ready = TRUE;
    return listener;
}
