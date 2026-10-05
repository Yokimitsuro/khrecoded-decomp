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
} CollisionWorld;

extern MeshNamedEntry *func_020338d4(MeshData *mesh, const char *name);
extern CollisionWorld *gActorRegistry;

void SetWorldMeshEntryValueByName(const char *name, const u32 *value)
{
    CollisionWorld *world = gActorRegistry;
    int meshIndex;

    for (meshIndex = 0; meshIndex < world->meshCount; meshIndex++) {
        MeshData *mesh = world->meshes[meshIndex];
        if (mesh != NULL) {
            MeshNamedEntry *entry = func_020338d4(mesh, name);
            if (entry != NULL) {
                entry->value = *value;
                return;
            }
        }
    }
}
