#include "nitro/types.h"

typedef struct ClassDescriptor {
    u16 classId;
    u16 subId;
    void *(*construct)(void *arg);
    void *method;
    u32 workSize;
    void ***heapRef;
} ClassDescriptor;

typedef struct TaskObject {
    u32 flags;
    struct TaskObject *parent;
    struct TaskObject *prev;
    struct TaskObject *next;
    u16 classId;
    u16 subId;
    void *state;
    void *method;
    void **heap;
    void *work;
    u32 workSize;
    u32 unk_28;
} TaskObject;

typedef struct TaskManager {
    u32 unk_00;
    TaskObject *current;
} TaskManager;

extern TaskManager gTaskManager;
extern void *SetDefaultHeap(void *heap);
extern void *NNSi_FndAllocFromExpHeapEx(u32 size, void **heap);
extern void *AllocFromHeapOrDefaultEx(u32 size, int align, void **heap);
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern void Obj_LinkNode(TaskObject *object);

TaskObject *Obj_Construct(TaskObject *object, ClassDescriptor *desc, void *ctorArg, int useTailAlloc)
{
    void **heap;
    void *savedHeap;
    TaskObject *savedCurrent;

    heap = NULL;
    object->flags = 0;
    object->parent = gTaskManager.current;
    object->classId = desc->classId;
    object->subId = desc->subId;
    if (desc->heapRef != NULL) {
        heap = *desc->heapRef;
    }
    object->heap = heap;
    object->workSize = desc->workSize;
    object->state = NULL;
    object->method = desc->method;
    object->unk_28 = 0;
    savedHeap = SetDefaultHeap(heap);
    if (object->workSize != 0) {
        if (useTailAlloc != 0) {
            object->work = AllocFromHeapOrDefaultEx(object->workSize, -4, object->heap);
        } else {
            object->work = NNSi_FndAllocFromExpHeapEx(object->workSize, object->heap);
        }
        MI_CpuFill8(object->work, 0, object->workSize);
    } else {
        object->work = NULL;
    }
    Obj_LinkNode(object);
    savedCurrent = gTaskManager.current;
    gTaskManager.current = object;
    gTaskManager.current->state = desc->construct(ctorArg);
    gTaskManager.current = savedCurrent;
    SetDefaultHeap(savedHeap);
    return object;
}
