#include "nitro/types.h"

typedef struct {
    void **objects;
    s8 count;
    u8 pad_05[7];
    void *resource;
    void *buffer;
} FieldObjectManager;

extern FieldObjectManager *data_ov001_020a04f8;
extern void func_ov001_0208743c(void);
extern void func_ov001_02086de0(void);
extern void FieldObjectClass_Destroy(void *object);
extern void ZeroHalfThenFree(void *resource);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);
extern void StoreGlobalArrayEntry(int index, int value);

void DestroyFieldObjectManager(void)
{
    FieldObjectManager *manager = data_ov001_020a04f8;
    int i;

    func_ov001_0208743c();
    func_ov001_02086de0();
    for (i = 0; i < manager->count; i++) {
        if (manager->objects[i] != NULL) {
            FieldObjectClass_Destroy(manager->objects[i]);
            manager->objects[i] = NULL;
        }
    }
    if (manager->resource != NULL) {
        ZeroHalfThenFree(manager->resource);
    }
    if (manager->buffer != NULL) {
        NNSi_FndFreeFromDefaultHeap(manager->buffer);
    }
    if (manager->objects != NULL) {
        NNSi_FndFreeFromDefaultHeap(manager->objects);
    }
    NNSi_FndFreeFromDefaultHeap(data_ov001_020a04f8);
    data_ov001_020a04f8 = NULL;
    StoreGlobalArrayEntry(4, 0);
}
