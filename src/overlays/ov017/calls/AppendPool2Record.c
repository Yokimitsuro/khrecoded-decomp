#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct MotionRecord {
    int kind;
    VecFx32 start;
    VecFx32 end;
    int param0;
    int param1;
    int param2;
} MotionRecord;

typedef struct PoolManager {
    u8 pad_000[0x1c4];
    int *pool0;
    void *pool1;
    MotionRecord *pool2;
    void *pool3;
    int *pool4;
    s16 pool0Capacity;
    u16 pool0Count;
    s16 pool1Capacity;
    u16 pool1Count;
    s16 pool2Capacity;
    u16 pool2Count;
} PoolManager;

extern void InitMotionRecord(MotionRecord *record, int param0, int param1, const VecFx32 *start, const VecFx32 *end, int param2, int kind);

u16 AppendPool2Record(PoolManager *manager, int param0, int param1, const VecFx32 *start, const VecFx32 *end, int param2, int kind)
{
    u16 index = manager->pool2Count++;

    InitMotionRecord(&manager->pool2[index], param0, param1, start, end, param2, kind);
    return manager->pool2Count - 1;
}
