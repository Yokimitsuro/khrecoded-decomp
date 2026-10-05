#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct PanelOwner {
    u8 pad_00[0x59];
    u8 listId;
} PanelOwner;

typedef struct PanelBlock {
    u32 state;
    PanelOwner *owner;
    void *work;
    void (*update)(void);
    u8 shape[0x20];
    u16 flags;
    u8 tag;
    u8 kind;
    int param;
    VecFx32 position;
    u8 pad_44[3];
    u8 hitFlag;
    u8 pad_48;
    s8 sizeX;
    s8 sizeY;
    s8 sizeZ;
} PanelBlock;

#define BLOCK_UNIT 0x1800

extern PanelBlock *func_ov001_02086330(void *owner, int kind);
extern void BuildCollisionShape(void *shape, const VecFx32 *position, int kind, fx32 sizeX, fx32 sizeY, fx32 sizeZ, s32 angle, BOOL allocate, int mode);
extern void AppendNodeToActiveList(u8 listId, int kind, u8 tag);

u8 SpawnPanelBlock(void *owner, int kind, u8 tag, int unused3, int unused4, const VecFx32 *position, s8 sizeX, s8 sizeY, s8 sizeZ, int param)
{
    PanelBlock *entry = func_ov001_02086330(owner, kind);
    PanelOwner *parent = entry->owner;

    entry->position = *position;
    entry->hitFlag = 0;
    entry->param = param;
    entry->position.x += (sizeX * BLOCK_UNIT >> 1) - (BLOCK_UNIT >> 1);
    entry->position.z += (sizeZ * BLOCK_UNIT >> 1) - (BLOCK_UNIT >> 1);
    entry->flags |= 0x10;
    entry->sizeX = sizeX;
    entry->sizeY = sizeY;
    entry->sizeZ = sizeZ;
    entry->update = NULL;
    BuildCollisionShape(entry->shape, &entry->position, 3, entry->sizeX * BLOCK_UNIT, entry->sizeY * BLOCK_UNIT, entry->sizeZ * BLOCK_UNIT, 0, 1, 4);
    entry->tag = tag;
    AppendNodeToActiveList(parent->listId, kind, entry->tag);
    return entry->tag;
}
