#include "nitro/types.h"

typedef struct MeshNamedEntry {
    char name[0xc];
    u8 pad_0c[0x8];
} MeshNamedEntry;

typedef struct MeshData {
    u8 pad_00[0xac];
    MeshNamedEntry *namedEntries;
} MeshData;

typedef struct CollisionWorld {
    u16 unk_00;
    u16 meshCount;
    MeshData **meshes;
} CollisionWorld;

extern CollisionWorld *data_0206083c;

MeshNamedEntry *GetWorldMeshNamedEntry(int index)
{
    MeshData *mesh = data_0206083c->meshes[0];
    if (index == 0xff) {
        return NULL;
    }
    return &mesh->namedEntries[index];
}
