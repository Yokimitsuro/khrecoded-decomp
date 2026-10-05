#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x18];
    void *objectHeap;
    u8 pad_1c[0x18];
    void *heap;
    void *savedHeap;
} HeapScope;

typedef struct {
    u8 pad_00[0x18e14];
    HeapScope heapScope;
} StageManager;

typedef struct {
    u8 pad_00[0x78];
    u32 isActive;
} ObjBase;

typedef struct {
    u8 pad_00[0x10];
    ObjBase base;
} StageObject;

extern StageManager *data_ov001_020a0528;
extern void *Heap_GetCurrent(void);
extern void *SetDefaultHeap(void *heap);
extern void ActorSlot_Unlink(StageObject *obj);
extern void func_020359c4(StageObject *obj);
extern void Obj_ShutdownBase(void *entity);

void ShutdownStageObject(StageObject *obj)
{
    StageManager *manager;
    ObjBase *base = &obj->base;

    if (base->isActive == 0) {
        return;
    }
    base->isActive = 0;
    manager = data_ov001_020a0528;
    if (manager != NULL && &manager->heapScope != NULL && manager->heapScope.savedHeap == NULL) {
        manager->heapScope.savedHeap = Heap_GetCurrent();
        SetDefaultHeap(manager->heapScope.objectHeap);
    }
    ActorSlot_Unlink(obj);
    func_020359c4(obj);
    manager = data_ov001_020a0528;
    if (manager != NULL && &manager->heapScope != NULL && manager->heapScope.savedHeap != NULL) {
        SetDefaultHeap(manager->heapScope.savedHeap);
        manager->heapScope.savedHeap = NULL;
    }
    Obj_ShutdownBase(&obj->base);
}
