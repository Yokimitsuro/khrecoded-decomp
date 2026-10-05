#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct GridManager {
    u8 pad_00[0x59];
    u8 listId;
} GridManager;

typedef struct GridObject {
    u8 pad_00[4];
    GridManager *manager;
    u8 pad_08[4];
    void *onQuery;
    u8 shape[0x20];
    u16 statusFlags;
    u8 slot;
    u8 pad_33;
    int userData;
    VecFx32 position;
    u16 objectId;
    u8 variant;
    u8 animIndex;
    u8 pad_48;
    s8 cellsX;
    s8 cellsY;
    s8 cellsZ;
} GridObject;

extern GridObject *func_ov001_02086330(void *pool, int kind);
extern void func_ov017_020a2a14(void);
extern void BuildCollisionShape(void *shape, const VecFx32 *position, int kind, fx32 sizeX, fx32 sizeY, fx32 sizeZ,
                                         s32 angle, BOOL allocate, int mask);
extern void AppendNodeToActiveList(u32 listId, u32 kind, u8 tag);

u8 SpawnGridObject(void *pool, int kind, int slot, u16 objectId, u8 variant, VecFx32 *position, s8 cellsX,
                            s8 cellsY, s8 cellsZ, int userData)
{
    GridObject *object = func_ov001_02086330(pool, kind);
    GridManager *manager = object->manager;

    object->position = *position;
    object->objectId = objectId;
    object->variant = variant;
    object->animIndex = 0;
    object->userData = userData;
    object->position.x += ((cellsX * 0x1800) >> 1) - 0xc00;
    object->position.z += ((cellsZ * 0x1800) >> 1) - 0xc00;
    object->position.x &= ~0x3f;
    object->position.y &= ~0x3f;
    object->statusFlags |= 0x10;
    object->cellsX = cellsX;
    object->cellsY = cellsY;
    object->cellsZ = cellsZ;
    object->onQuery = func_ov017_020a2a14;
    BuildCollisionShape(object->shape, &object->position, 3, object->cellsX * 0xc00, object->cellsY * 0xc00,
                                 object->cellsZ * 0xc00, 0, TRUE, 4);
    object->slot = slot;
    AppendNodeToActiveList(manager->listId, kind, object->slot);
    return object->slot;
}
