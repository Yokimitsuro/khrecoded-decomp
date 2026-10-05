#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef void (*PoolCallback)(void);

typedef struct Kind2EntryPool {
    PoolCallback callbacks[16];
    u8 pad_40[4];
    s32 selected;
    int active;
    u8 pad_4c[0xe];
    u8 kind;
} Kind2EntryPool;

extern Kind2EntryPool *CreateEntryPool(int headerSize, int entrySize, int count);
extern void func_ov020_020a20b0(void);
extern void func_ov020_020a21d4(void);
extern void DrawPanelBlockCells(void);
extern void func_ov020_020a21d8(void);
extern void TryCollideIdlePanel(void);
extern void func_ov020_020a2364(void);
extern void ProbeBlockGroundOffset(void);
extern void CollectPanelCellPositions(void);

Kind2EntryPool *CreateKind2EntryPool(int count)
{
    Kind2EntryPool *pool = CreateEntryPool(0x60, 0x50, count);

    pool->active = 0;
    pool->selected = -1;
    pool->callbacks[0] = func_ov020_020a20b0;
    pool->callbacks[2] = NULL;
    pool->callbacks[4] = NULL;
    pool->callbacks[5] = NULL;
    pool->callbacks[6] = func_ov020_020a21d4;
    pool->callbacks[14] = DrawPanelBlockCells;
    pool->callbacks[7] = func_ov020_020a21d8;
    pool->callbacks[8] = NULL;
    pool->callbacks[9] = TryCollideIdlePanel;
    pool->callbacks[10] = NULL;
    pool->callbacks[3] = func_ov020_020a2364;
    pool->callbacks[1] = ProbeBlockGroundOffset;
    pool->callbacks[11] = CollectPanelCellPositions;
    pool->kind = 2;
    return pool;
}
