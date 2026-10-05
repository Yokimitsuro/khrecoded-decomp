#include "nitro/types.h"

typedef struct Ov038SpritePool {
    u8 data[0x6434];
} Ov038SpritePool;

typedef struct Ov038Context {
    u8 pad_00[0x40];
    Ov038SpritePool pools[2];
} Ov038Context;

extern Ov038Context *data_ov038_020bd164;
extern void func_0204f218(void *pool, s32 recordIndex, u16 value);

void SetOv038PoolRecordFlags(s32 poolIndex, s32 recordIndex, int value)
{
    func_0204f218(&data_ov038_020bd164->pools[poolIndex], recordIndex, value);
}
