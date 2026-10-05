#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraPath {
    void *nodes;
    u16 nodeCount;
    u8 pad_06[0x46];
    s32 curveType;
    fx32 duration;
    void *links;
    u16 linkCount;
} CameraPath;

extern void NNSi_FndFreeFromDefaultHeap(void *block);

void CameraPath_Free(CameraPath *path)
{
    NNSi_FndFreeFromDefaultHeap(path->nodes);
    path->nodes = NULL;
    if (path->links != NULL) {
        NNSi_FndFreeFromDefaultHeap(path->links);
        path->links = NULL;
    }
}
