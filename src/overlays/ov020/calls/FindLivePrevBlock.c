#include "nitro/types.h"

typedef struct Block {
    u8 pad_00[4];
    void *pool;
    u8 pad_08[0x4c];
    u16 flags;
    s16 prevIndex;
    s16 nextIndex;
} Block;

extern Block *func_ov001_02086384(void *pool, int index);

static inline Block *GetPrevBlock(Block *block)
{
    return func_ov001_02086384(block->pool, block->prevIndex);
}

Block *FindLivePrevBlock(Block *block)
{
    while (block->prevIndex >= 0) {
        block = GetPrevBlock(block);
        if (!(block->flags & 0x8000)) {
            return block;
        }
    }
    return NULL;
}
