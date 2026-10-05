#include "nitro/types.h"

typedef struct MeshNamedEntry {
    char name[0xc];
    u32 value;
    void *data;
} MeshNamedEntry;

typedef struct MeshData MeshData;

typedef struct CollisionWorld {
    u16 unk_00;
    u16 meshCount;
    MeshData **meshes;
    u8 pad_08[0x828 - 0x8];
    u8 dataPool[0x100];
    u32 dataPoolUsed;
} CollisionWorld;

extern MeshNamedEntry *func_020338d4(MeshData *mesh, const char *name);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern CollisionWorld *data_0206083c;

void SetWorldMeshEntryDataByName(const char *name, const void *src, u32 size)
{
    CollisionWorld *world = data_0206083c;
    int meshIndex;

    for (meshIndex = 0; meshIndex < world->meshCount; meshIndex++) {
        MeshData *mesh = world->meshes[meshIndex];
        if (mesh != NULL) {
            MeshNamedEntry *entry = func_020338d4(mesh, name);
            if (entry != NULL) {
                u8 *dest = &data_0206083c->dataPool[data_0206083c->dataPoolUsed];
                data_0206083c->dataPoolUsed += size;
                MI_CpuCopy8(src, dest, size);
                entry->data = dest;
                return;
            }
        }
    }
}
