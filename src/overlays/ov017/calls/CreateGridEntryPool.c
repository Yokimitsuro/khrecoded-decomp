#include "nitro/types.h"

typedef void (*PoolCallback)(void);

typedef struct GridEntryPool {
    PoolCallback update;
    PoolCallback draw;
    void *field_08;
    PoolCallback onRemove;
    void *field_10;
    void *field_14;
    PoolCallback onInit;
    PoolCallback onEnter;
    void *field_20;
    PoolCallback onLeave;
    void *field_28;
    PoolCallback onQuery;
    u8 pad_30[0x8];
    PoolCallback onReset;
    u8 pad_3c[0x8];
    int selected;
    int active;
    u8 pad_4c[0xe];
    u8 kind;
} GridEntryPool;

extern GridEntryPool *CreateEntryPool(int headerSize, int entrySize, int count);
extern void RestoreGridObjectRecord(void);
extern void func_ov017_020a276c(void);
extern void func_ov017_020a288c(void);
extern void func_ov017_020a2770(void);
extern void CollideGridObjectActor(void);
extern void func_ov017_020a2888(void);
extern void func_ov017_020a28cc(void);
extern void BuildFieldObjectCellGrid(void);

GridEntryPool *CreateGridEntryPool(int count)
{
    GridEntryPool *pool = CreateEntryPool(0x60, 0x50, count);

    pool->active = 0;
    pool->selected = -1;
    pool->update = RestoreGridObjectRecord;
    pool->field_08 = NULL;
    pool->field_10 = NULL;
    pool->field_14 = NULL;
    pool->onInit = func_ov017_020a276c;
    pool->onReset = func_ov017_020a288c;
    pool->onEnter = func_ov017_020a2770;
    pool->field_20 = NULL;
    pool->onLeave = CollideGridObjectActor;
    pool->field_28 = NULL;
    pool->onRemove = func_ov017_020a2888;
    pool->draw = func_ov017_020a28cc;
    pool->onQuery = BuildFieldObjectCellGrid;
    pool->kind = 8;
    return pool;
}
