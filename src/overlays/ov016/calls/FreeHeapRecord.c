#include "nitro/types.h"

typedef struct FieldObject {
    u8 pad_00[0xBD];
    u8 flagsLow : 4;
    u8 stateLevel : 4;
    u8 pad_BE[0xEC - 0xBE];
    void *record;
} FieldObject;

extern void NNSi_FndFreeFromDefaultHeap(void *block);

void FreeHeapRecord(FieldObject *object)
{
    if (object->stateLevel >= 5 && object->record != NULL) {
        NNSi_FndFreeFromDefaultHeap(object->record);
    }
}
