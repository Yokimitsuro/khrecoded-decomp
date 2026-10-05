#include "nitro/types.h"

typedef struct ModelViewer ModelViewer;

extern void ReleaseViewerModels(ModelViewer *viewer);
extern void FreeModelFiles(ModelViewer *viewer);
extern void G3X_SetHOffset(u32 value);

void DestroyModelViewer(ModelViewer *viewer)
{
    ReleaseViewerModels(viewer);
    FreeModelFiles(viewer);
    G3X_SetHOffset(0);
}
