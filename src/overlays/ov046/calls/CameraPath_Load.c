#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraPathNode {
    u32 view[17];
    s32 curveType;
    fx32 duration;
} CameraPathNode;

typedef struct CameraPathKey {
    u32 data[7];
} CameraPathKey;

typedef struct CameraPath {
    CameraPathNode *nodes;
    u16 nodeCount;
    u16 currentNode;
    u8 pad_08[0x44];
    s32 curveType;
    fx32 duration;
    CameraPathKey *keys;
    u16 keyCount;
} CameraPath;

extern void *func_0202c4a0(u32 fileId, u32 kind);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void MIi_CpuCopyFast(const void *src, void *dst, u32 size);

void CameraPath_Load(CameraPath *path, u32 fileId)
{
    u32 *file = func_0202c4a0(fileId, 0x11);
    u32 *durationField = file + 1;
    u32 *curveField = durationField + 1;
    u32 *countField = curveField + 1;
    u32 *keyData;

    path->curveType = *curveField;
    path->duration = *durationField;
    path->nodeCount = *countField;
    path->nodes = NNSi_FndAllocFromDefaultHeap(path->nodeCount * sizeof(CameraPathNode));
    MIi_CpuCopyFast(countField + 1, path->nodes, path->nodeCount * sizeof(CameraPathNode));
    keyData = (u32 *)((CameraPathNode *)(countField + 1) + path->nodeCount);
    path->keyCount = *keyData;
    if (path->keyCount != 0) {
        path->keys = NNSi_FndAllocFromDefaultHeap(path->keyCount * sizeof(CameraPathKey));
        MIi_CpuCopyFast(keyData + 1, path->keys, path->keyCount * sizeof(CameraPathKey));
    } else {
        path->keys = NULL;
    }
    NNSi_FndFreeFromDefaultHeap(file);
}
