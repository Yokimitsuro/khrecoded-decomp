#pragma thumb on

#include "nitro/types.h"

typedef struct {
    u16 flags;
    volatile u16 count;
    void **models;
} ModelGroup;

extern int IndexedPointer_GetFirstWord(void *pack, int kind);
extern void *NestedPointer_GetFirstWord(void *pack, int kind, int index);
extern void *NNSi_FndAllocFromDefaultHeap(unsigned int size);
extern void InitMeshData(void *model);

int ModelGroup_Open(ModelGroup *g, void *res)
{
    int i;

    g->flags = 0;
    if (*(unsigned int *)res == 0x4850414b) {
        g->count = IndexedPointer_GetFirstWord(res, 5);
        g->models = NNSi_FndAllocFromDefaultHeap(g->count << 2);
        for (i = 0; i < g->count; i++) {
            g->models[i] = NestedPointer_GetFirstWord(res, 5, i);
            InitMeshData(g->models[i]);
        }
    } else {
        g->count = 1;
        g->models = NNSi_FndAllocFromDefaultHeap(4);
        g->models[0] = res;
        InitMeshData(g->models[0]);
    }
    return 1;
}
