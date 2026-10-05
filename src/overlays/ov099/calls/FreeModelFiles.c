#include "nitro/types.h"

typedef struct {
    void *modelData;
    void *models[40];
    void *sourceFile;
} ModelViewer;

extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void ZeroHalfThenFree(void *file);

void FreeModelFiles(ModelViewer *viewer)
{
    NNSi_FndFreeFromDefaultHeap(viewer->modelData);
    ZeroHalfThenFree(viewer->sourceFile);
}
