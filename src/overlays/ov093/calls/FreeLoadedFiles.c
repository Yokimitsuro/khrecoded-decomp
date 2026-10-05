#include "nitro/types.h"

typedef struct {
    void *loadedFiles[3];
} SceneWork;

extern void ZeroHalfThenFree(void *file);

void FreeLoadedFiles(SceneWork *work)
{
    int i;

    for (i = 0; i < 3; i++) {
        ZeroHalfThenFree(work->loadedFiles[i]);
    }
}
