#include "nitro/types.h"

typedef struct Ov038SpritePool {
    u8 data[0x6434];
} Ov038SpritePool;

typedef struct Ov038Context {
    u8 pad_00[0x40];
    Ov038SpritePool pools[2];
} Ov038Context;

extern Ov038Context *data_ov038_020bd164;
extern void func_0204f218(void *pool, s32 recordIndex, u16 cell);
extern void IndexedRecords_SetFlag2(void *pool, s32 recordIndex, BOOL visible);

void DrawScoreDigits(s32 poolIndex, s32 firstRecord, s32 value)
{
    s32 offset = poolIndex * sizeof(Ov038SpritePool);
    u8 *pools = (u8 *)data_ov038_020bd164->pools;
    BOOL visible = FALSE;
    s32 divisor = 100000;
    s32 index;
    u16 digit;

    if (999999 < value) {
        value = 999999;
    }
    for (index = 0; index < 6; index++) {
        digit = value / divisor;
        if (digit != 0 || index == 5) {
            visible = TRUE;
        }
        value = value % divisor;
        divisor = divisor / 10;
        func_0204f218(pools + offset, firstRecord + index, digit);
        IndexedRecords_SetFlag2(pools + offset, firstRecord + index, visible);
    }
}

