#include "nitro/types.h"

typedef struct FieldObjectClass {
    u8 pad_00[0x64];
    s16 workIndex;
} FieldObjectClass;

typedef struct FieldObject {
    struct FieldObject *prev;
    struct FieldObject *next;
    FieldObjectClass *objectClass;
    void *work;
    u8 pad_10[0x29];
    u8 classKind;
    u8 slotIndex;
    u8 pad_3B[0x13];
    u16 flags;
    u16 saveBitOffset;
    u8 saveBitCount;
    u32 unk_54;
} FieldObject;

extern FieldObject *func_ov001_0207f4dc(FieldObjectClass *objectClass, int slotIndex);
extern u8 FindRegisteredEntryIndex(FieldObjectClass *objectClass);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void MIi_CpuClearFast(u32 value, void *dest, u32 size);

FieldObject *FieldObject_Create(FieldObjectClass *objectClass, u8 slotIndex)
{
    FieldObject *object = func_ov001_0207f4dc(objectClass, slotIndex);

    if (object->flags != 0) {
        return NULL;
    }
    object->prev = NULL;
    object->next = NULL;
    object->flags = 1;
    object->objectClass = objectClass;
    object->classKind = FindRegisteredEntryIndex(objectClass);
    object->slotIndex = slotIndex;
    object->saveBitOffset = 0xffff;
    object->saveBitCount = 0;
    object->unk_54 = 0;
    if (objectClass->workIndex >= 0) {
        object->work = NNSi_FndAllocFromDefaultHeap(0x1d0);
        MIi_CpuClearFast(0, object->work, 0x1d0);
    } else {
        object->work = NULL;
    }
    return object;
}
