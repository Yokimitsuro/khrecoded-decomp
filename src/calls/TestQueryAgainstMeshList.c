#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x74];
    u16 flags;
} CollisionMesh;

typedef struct {
    u16 unk_00;
    u16 meshCount;
    CollisionMesh **meshes;
} CollisionMeshList;

typedef struct {
    u8 data[0x114];
} CollisionQuery;

extern void InitGatherQueryFromParams(CollisionQuery *query, void *params);
extern void GatherModelFaces(CollisionQuery *query, CollisionMesh *mesh);

void TestQueryAgainstMeshList(CollisionMeshList *list, void *params)
{
    CollisionQuery query;
    int i;
    int count = list->meshCount;
    InitGatherQueryFromParams(&query, params);
    for (i = 0; i < count; i++) {
        CollisionMesh *mesh = list->meshes[i];
        if ((mesh->flags & 0x2000) == 0) {
            GatherModelFaces(&query, mesh);
        }
    }
}
