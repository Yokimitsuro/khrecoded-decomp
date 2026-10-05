#include "nitro/types.h"

typedef struct HeapBlock HeapBlock;

typedef struct FieldObject {
    u8 pad_00[0x6c];
    u8 resource[0x170 - 0x6c];
    s16 soundHandle;
    u8 pad_172[0x1c4 - 0x172];
    void *buffers[4];
    HeapBlock **valueSlots;
    u8 pad_1d8[0x1ea - 0x1d8];
    u16 valueSlotCount;
} FieldObject;

extern void ReleaseResourceAndDetach(void *resource);
extern void func_ov021_020a8a88(int handle);
extern void FreeBlockChain(HeapBlock **head);
extern void ReleaseIfSet(void **ptr);

void ReleaseFieldObjectResources(FieldObject *object)
{
    int index;

    ReleaseResourceAndDetach(object->resource);
    func_ov021_020a8a88(object->soundHandle);
    for (index = 0; index < object->valueSlotCount; index++) {
        FreeBlockChain(&object->valueSlots[index]);
    }
    ReleaseIfSet(&object->buffers[0]);
    ReleaseIfSet(&object->buffers[1]);
    ReleaseIfSet(&object->buffers[2]);
    ReleaseIfSet(&object->buffers[3]);
    ReleaseIfSet((void **)&object->valueSlots);
}
