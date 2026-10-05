#include "nitro/types.h"

typedef struct {
    u32 entryFlags[3][64];
    void *loadedFiles[3];
} SceneWork;

extern void ZeroHalfThenFree(void *file);

void FreeLoadedFiles_020bf454(SceneWork *work)
{
    int i;

    for (i = 0; i < 3; i++) {
        ZeroHalfThenFree(work->loadedFiles[i]);
    }
}
