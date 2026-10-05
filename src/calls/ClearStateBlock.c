#include "nitro/types.h"

typedef struct StateBlock {
    u8 pad_00[0xC4];
    u32 unk_C4;
    u8 pad_C8[0x4];
} StateBlock;

extern void MI_CpuFill8(void *dst, int value, int size);

void ClearStateBlock(StateBlock *block)
{
    MI_CpuFill8(block, 0, sizeof(StateBlock));
    block->unk_C4 = 0;
}
