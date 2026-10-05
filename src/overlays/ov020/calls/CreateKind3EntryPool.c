#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef void (*PoolCallback)(void);

typedef struct Kind3EntryPool {
    PoolCallback callbacks[16];
    u8 pad_40[4];
    s32 selected;
    int active;
    u8 pad_4c[0xe];
    u8 kind;
} Kind3EntryPool;

extern Kind3EntryPool *CreateEntryPool(int headerSize, int entrySize, int count);
extern void LoadPanelStackPhase(void);
extern void func_ov020_020a3598(void);
extern void DrawStackedPanels(void);
extern void func_ov020_020a359c(void);
extern void TryCollidePanelShape(void);
extern void TryGetFieldHandle_020a3720(void);

Kind3EntryPool *CreateKind3EntryPool(int count)
{
    Kind3EntryPool *pool = CreateEntryPool(0x60, 0x5c, count);

    pool->active = 0;
    pool->selected = -1;
    pool->callbacks[0] = LoadPanelStackPhase;
    pool->callbacks[2] = NULL;
    pool->callbacks[4] = NULL;
    pool->callbacks[5] = NULL;
    pool->callbacks[6] = func_ov020_020a3598;
    pool->callbacks[14] = DrawStackedPanels;
    pool->callbacks[7] = func_ov020_020a359c;
    pool->callbacks[9] = TryCollidePanelShape;
    pool->callbacks[8] = TryGetFieldHandle_020a3720;
    pool->callbacks[10] = NULL;
    pool->kind = 3;
    return pool;
}
