#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct BlockOwner {
    u8 pad_00[0x59];
    u8 listId;
} BlockOwner;

typedef struct StackedBlock {
    u32 state;
    BlockOwner *owner;
    void *work;
    void (*update)(void);
    u8 shape[0x20];
    u16 renderFlags;
    u8 tag;
    u8 kind;
    int param;
    VecFx32 position;
    u8 pad_44[3];
    u8 hitFlag;
    int timer;
    s8 linkA;
    s8 linkB;
    u8 pad_4e[2];
    u8 mode;
    s8 group;
    u8 pad_52[2];
    u16 flags;
    s16 next;
    s16 prev;
    s16 base;
    fx32 baseHeight;
} StackedBlock;

extern StackedBlock *func_ov001_02086330(void *owner, int kind);
extern void BuildCollisionShape(void *shape, const VecFx32 *position, int kind, fx32 sizeX, fx32 sizeY, fx32 sizeZ, s32 angle, BOOL allocate, int mode);
extern void AppendNodeToActiveList(u8 listId, int kind, u8 tag);
extern void UpdateStackedBlock(void);

u8 SpawnStackedBlock(void *owner, int kind, u8 tag, int unused3, int unused4, const VecFx32 *position,
                              s8 linkA, s8 linkB, s16 next, s16 prev, s16 base, s8 group, int param)
{
    StackedBlock *entry = func_ov001_02086330(owner, kind);
    BlockOwner *parent = entry->owner;

    entry->position = *position;
    entry->hitFlag = 0;
    entry->param = param;
    entry->mode = 0;
    entry->flags = 0;
    entry->timer = 0;
    entry->linkA = linkA;
    entry->linkB = linkB;
    entry->next = next;
    entry->prev = prev;
    entry->base = base;
    entry->baseHeight = entry->position.y;
    entry->group = group;
    if (entry->prev < 0) {
        entry->flags |= 1;
    }
    if (entry->flags & 0x8000) {
        entry->update = NULL;
        entry->mode = 2;
    } else {
        entry->update = UpdateStackedBlock;
        BuildCollisionShape(entry->shape, &entry->position, 3, 0x1800, 0x1800, 0x1800, 0, 1, 4);
        entry->renderFlags |= 8;
        entry->renderFlags |= 0x10;
    }
    if (entry->linkB >= 0) {
        entry->flags |= 0x200;
    }
    entry->tag = tag;
    AppendNodeToActiveList(parent->listId, kind, entry->tag);
    return entry->tag;
}
