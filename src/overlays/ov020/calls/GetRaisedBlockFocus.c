#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Block {
    u8 pad_00[0x38];
    VecFx32 position;
    u8 pad_44[0xc];
    s8 state;
    u8 pad_51[3];
    u16 flags;
    u8 pad_56[0xe];
    VecFx32 focusPoint;
} Block;

VecFx32 *GetRaisedBlockFocus(Block *block)
{
    if (!(block->flags & 8) && block->state == 0) {
        block->focusPoint = block->position;
        block->focusPoint.y += 0x600;
        return &block->focusPoint;
    }
    return NULL;
}
