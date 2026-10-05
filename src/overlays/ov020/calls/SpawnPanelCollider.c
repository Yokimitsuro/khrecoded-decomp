#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct PanelOwner {
    u8 pad_00[0x59];
    u8 listId;
} PanelOwner;

typedef struct PanelCollider {
    u32 state;
    PanelOwner *owner;
    void *work;
    void (*update)(void);
    u8 shape[0x20];
    u16 flags;
    u8 tag;
    u8 kind;
    u8 pad_34[4];
    VecFx32 position;
    u8 pad_44[3];
    u8 hitFlag;
    u8 hitCount;
    u8 enabled;
    u8 pad_4a[2];
    int timer;
    int target;
} PanelCollider;

extern const VecFx32 data_0205344c;
extern PanelCollider *func_ov001_02086330(void *owner, int kind);
extern void BuildCollisionShape(void *shape, const VecFx32 *position, int kind, fx32 sizeX, fx32 sizeY, fx32 sizeZ, s32 angle, BOOL allocate, int mode);
extern void AppendNodeToActiveList(u8 listId, int kind, u8 tag);
extern void func_ov020_020a37f8(void);

u8 SpawnPanelCollider(void *owner, int kind, u8 tag, const VecFx32 *position)
{
    PanelCollider *entry = func_ov001_02086330(owner, kind);
    PanelOwner *parent = entry->owner;

    entry->position = data_0205344c;
    entry->hitFlag = 0;
    entry->position = *position;
    entry->flags |= 0x10;
    entry->target = 0;
    entry->timer = 0;
    entry->hitCount = 0;
    entry->enabled = 1;
    entry->update = func_ov020_020a37f8;
    BuildCollisionShape(entry->shape, &entry->position, 3, 0x1800, 0x1800, 0x1800, 0, 1, 4);
    entry->tag = tag;
    AppendNodeToActiveList(parent->listId, kind, entry->tag);
    return entry->tag;
}
