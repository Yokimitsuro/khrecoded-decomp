#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    void *work;
    void *resource;
    u8 pad_14[0x24];
    u8 classKind;
    u8 pad_39[0x15];
    u16 flags;
} FieldObject;

typedef struct FieldObjectClass {
    u8 pad_00[0x18];
    void (*onObjectDestroy)(FieldObject *object);
    void (*onClassDestroy)(struct FieldObjectClass *objectClass);
    u8 pad_20[0x26];
    u16 slotCount;
} FieldObjectClass;

extern FieldObject *GetStridedBufferEntry(FieldObjectClass *objectClass, int slotIndex);
extern void Obj_ConditionalShutdown(void *object, u16 arg);
extern void ReleaseResourceAndDetach(void *resource);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);

void FieldObjectClass_Destroy(FieldObjectClass *objectClass)
{
    u16 count = objectClass->slotCount;
    FieldObject *object;
    int i;

    for (i = 0; i < count; i++) {
        object = GetStridedBufferEntry(objectClass, i);
        if (object->flags & 1) {
            if (objectClass->onObjectDestroy != NULL) {
                objectClass->onObjectDestroy(object);
            }
            if (object->work != NULL) {
                Obj_ConditionalShutdown(object->work, object->classKind);
                NNSi_FndFreeFromDefaultHeap(object->work);
                object->work = NULL;
            }
            if (object->resource != NULL) {
                ReleaseResourceAndDetach(object->resource);
                NNSi_FndFreeFromDefaultHeap(object->resource);
                object->resource = NULL;
            }
        }
    }
    if (objectClass->onClassDestroy != NULL) {
        objectClass->onClassDestroy(objectClass);
    }
    NNSi_FndFreeFromDefaultHeap(objectClass);
}
