#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct EntryManager {
    u8 pad_00[0x59];
    u8 listId;
} EntryManager;

typedef struct Kind7Entry {
    u8 pad_00[4];
    EntryManager *manager;
    u8 pad_08[4];
    void *onQuery;
    u8 shape[0x20];
    u16 statusFlags;
    u8 slot;
    u8 pad_33;
    fx32 speed;
    VecFx32 position;
    u16 objectId;
    u8 variant;
    u8 animIndex;
    int timer;
    s8 linkIndex;
    s8 linkGroup;
    u8 pad_4E[2];
    s8 state;
    s8 style;
    u8 pad_52[2];
    u16 flags;
    s16 belowIndex;
    s16 parentIndex;
    s16 anchorIndex;
    fx32 baseY;
} Kind7Entry;

extern Kind7Entry *func_ov001_02086330(void *pool, int kind);
extern void func_ov017_020a5900(void);
extern void BuildCollisionShape(void *shape, const VecFx32 *position, int kind, fx32 sizeX, fx32 sizeY, fx32 sizeZ,
                                         s32 angle, BOOL allocate, int mask);
extern void func_ov001_020645dc(int objectId);
extern void AppendNodeToActiveList(u32 listId, u32 kind, u8 tag);

u8 SpawnKind7Entry(void *pool, int kind, int slot, u16 objectId, u8 variant, VecFx32 *position, s8 linkIndex,
                            s8 linkGroup, s16 belowIndex, s16 parentIndex, s16 anchorIndex, s8 style, fx32 speed,
                            BOOL persistent)
{
    Kind7Entry *entry = func_ov001_02086330(pool, kind);
    EntryManager *manager = entry->manager;
    BOOL active;

    entry->position = *position;
    entry->objectId = objectId;
    entry->variant = variant;
    entry->animIndex = 0;
    entry->speed = speed;
    entry->state = 0;
    entry->flags = 0;
    entry->timer = 0;
    entry->linkIndex = linkIndex;
    entry->linkGroup = linkGroup;
    entry->belowIndex = belowIndex;
    entry->parentIndex = parentIndex;
    entry->anchorIndex = anchorIndex;
    entry->baseY = entry->position.y;
    entry->style = style;
    entry->position.x &= ~0x3f;
    entry->position.y &= ~0x3f;
    if (entry->parentIndex < 0) {
        entry->flags |= 1;
    }
    active = TRUE;
    if (entry->state != 2 && entry->state != 1) {
        active = FALSE;
    }
    if (active) {
        entry->onQuery = NULL;
        entry->state = 2;
    } else {
        entry->onQuery = func_ov017_020a5900;
        BuildCollisionShape(entry->shape, &entry->position, 3, 0xc00, 0xc00, 0xc00, 0, TRUE, 4);
        entry->statusFlags |= 8;
        entry->statusFlags |= 0x10;
    }
    if (entry->linkGroup >= 0 || entry->linkGroup == -2) {
        entry->flags |= 0x200;
    }
    if (entry->linkIndex >= 0 && entry->linkGroup < 0) {
        func_ov001_020645dc(objectId);
    } else if (persistent) {
        entry->flags |= 0x400;
    }
    entry->slot = slot;
    AppendNodeToActiveList(manager->listId, kind, entry->slot);
    return entry->slot;
}
