#include "nitro/types.h"

typedef struct MeshNamedEntry {
    char name[0xc];
    u8 pad_0c[0x8];
} MeshNamedEntry;

typedef struct MeshData {
    u8 pad_00[0x82];
    u16 namedEntryCount;
    u8 pad_84[0xac - 0x84];
    MeshNamedEntry *namedEntries;
} MeshData;

typedef struct CollisionWorld {
    u16 unk_00;
    u16 meshCount;
    MeshData **meshes;
} CollisionWorld;

extern int strncmp(const unsigned char *s1, const unsigned char *s2, unsigned int n);
extern CollisionWorld *data_0206083c;

MeshNamedEntry *FindWorldMeshEntryByName(const char *name)
{
    int meshIndex;
    MeshNamedEntry *entry;
    int entryIndex;
    int entryCount;
    MeshData **meshes;
    int meshCount;
    MeshData *mesh;

    meshCount = data_0206083c->meshCount;
    meshIndex = 0;
    if (meshCount > 0) {
        meshes = data_0206083c->meshes;
        do {
            mesh = meshes[meshIndex];
            if (mesh != NULL) {
                entryCount = mesh->namedEntryCount;
                entryIndex = 0;
                entry = mesh->namedEntries;
                if (entryCount > 0) {
                    do {
                        if (strncmp((const unsigned char *)entry->name, (const unsigned char *)name, 8) == 0) {
                            return entry;
                        }
                        entryIndex++;
                        entry++;
                    } while (entryIndex < entryCount);
                }
            }
            meshIndex++;
        } while (meshIndex < meshCount);
    }
    return NULL;
}
