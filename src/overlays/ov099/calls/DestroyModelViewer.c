#include "nitro/types.h"

typedef struct ModelViewer ModelViewer;

extern void func_ov099_020c1d20(ModelViewer *viewer);
extern void FreeModelFiles(ModelViewer *viewer);
extern void G3X_SetHOffset(u32 value);

void DestroyModelViewer(ModelViewer *viewer)
{
    func_ov099_020c1d20(viewer);
    FreeModelFiles(viewer);
    G3X_SetHOffset(0);
}
