#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef void (*PoolCallback)(void);

typedef struct PanelEntryPool {
    PoolCallback callbacks[16];
    u8 pad_40[4];
    fx32 range;
    int active;
    VecFx32 extent;
    u8 mode;
    u8 pad_59;
    u8 kind;
} PanelEntryPool;

extern PanelEntryPool *CreateEntryPool(int headerSize, int entrySize, int count);
extern void func_ov020_020a2924(void);
extern void func_ov020_020a3170(void);
extern void ReleaseAndFreeResource(void);
extern void func_ov020_020a2af8(void);
extern void TryGetFieldHandle(void);
extern void TryCollideWithCollider_020a2cb8(void);
extern void GetRaisedBlockFocus(void);
extern void ApplyTypeCapabilityFlag(void);
extern void func_ov020_020a2850(void);
extern void func_ov020_020a2edc(void);

PanelEntryPool *CreatePanelEntryPool(int count)
{
    PanelEntryPool *pool = CreateEntryPool(0x60, 0x70, count);

    pool->active = 0;
    pool->mode = 3;
    pool->extent.x = 0x1800;
    pool->extent.y = 0x1800;
    pool->extent.z = 0x1800;
    pool->range = 0x3000;
    pool->callbacks[0] = func_ov020_020a2924;
    pool->callbacks[1] = func_ov020_020a3170;
    pool->callbacks[2] = NULL;
    pool->callbacks[4] = ReleaseAndFreeResource;
    pool->callbacks[5] = NULL;
    pool->callbacks[6] = NULL;
    pool->callbacks[7] = func_ov020_020a2af8;
    pool->callbacks[8] = TryGetFieldHandle;
    pool->callbacks[9] = TryCollideWithCollider_020a2cb8;
    pool->callbacks[10] = GetRaisedBlockFocus;
    pool->callbacks[3] = ApplyTypeCapabilityFlag;
    pool->callbacks[12] = func_ov020_020a2850;
    pool->callbacks[14] = func_ov020_020a2edc;
    pool->kind = 1;
    return pool;
}
