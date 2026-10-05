#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef void (*PoolCallback)(void);

typedef struct Kind7EntryPool {
    PoolCallback callbacks[16];
    u8 pad_40[4];
    fx32 range;
    int active;
    VecFx32 extent;
    u8 mode;
    u8 pad_59;
    u8 kind;
} Kind7EntryPool;

extern Kind7EntryPool *CreateEntryPool(int headerSize, int entrySize, int count);
extern void LoadStageObjectPhase(void);
extern void SyncKind7EntryStackHeight(void);
extern void ReleaseField48(void);
extern void func_ov017_020a5474(void);
extern void GetListHead(void);
extern void CollideKind7Entry(void);
extern void GetRaisedPosition(void);
extern void func_ov017_020a5a98(void);
extern void IsActiveAncestorChain(void);
extern void DrawKind7EntryStack(void);

Kind7EntryPool *CreateKind7EntryPool(int count)
{
    Kind7EntryPool *pool = CreateEntryPool(0x60, 0x70, count);

    pool->active = 0;
    pool->mode = 3;
    pool->extent.x = 0x1800;
    pool->extent.y = 0x1800;
    pool->extent.z = 0x1800;
    pool->range = 0x3000;
    pool->callbacks[0] = LoadStageObjectPhase;
    pool->callbacks[1] = SyncKind7EntryStackHeight;
    pool->callbacks[2] = NULL;
    pool->callbacks[4] = ReleaseField48;
    pool->callbacks[5] = NULL;
    pool->callbacks[6] = NULL;
    pool->callbacks[7] = func_ov017_020a5474;
    pool->callbacks[8] = GetListHead;
    pool->callbacks[9] = CollideKind7Entry;
    pool->callbacks[10] = GetRaisedPosition;
    pool->callbacks[3] = func_ov017_020a5a98;
    pool->callbacks[12] = IsActiveAncestorChain;
    pool->callbacks[14] = DrawKind7EntryStack;
    pool->kind = 7;
    return pool;
}
