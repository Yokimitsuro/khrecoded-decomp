#include "nitro/types.h"

typedef struct MeshHeader {
    u8 pad_00[0x10];
    u16 flags;
} MeshHeader;

extern u8 data_02060780;

void SetMeshEnabled(void *unused, MeshHeader *mesh, BOOL enable) {
    if (enable) {
        mesh->flags = mesh->flags & ~0x4000;
        data_02060780++;
        return;
    }
    mesh->flags = mesh->flags | 0x4000;
    data_02060780++;
}
