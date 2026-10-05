#include "nitro/types.h"

typedef struct FieldObjectClass {
    u8 pad_00[0x44];
    u16 objectSize;
    u16 objectCount;
    void *objects;
} FieldObjectClass;

extern void *GetStridedBufferEntry(FieldObjectClass *objectClass, int slotIndex);
extern void FieldObject_ResetToIdle(void *object);
extern void FieldGroup_ShufflePositions(FieldObjectClass *objectClass);

void FieldObjects_ResetAllAndShuffle(FieldObjectClass *objectClass)
{
    int slotIndex;
    int count = objectClass->objectCount;

    for (slotIndex = 0; slotIndex < count; slotIndex++) {
        FieldObject_ResetToIdle(GetStridedBufferEntry(objectClass, slotIndex));
    }
    FieldGroup_ShufflePositions(objectClass);
}
