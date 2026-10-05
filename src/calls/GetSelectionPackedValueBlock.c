#include "nitro/types.h"

typedef struct PackedValueBlock {
    u32 savedByte;
    u16 values[3];
} PackedValueBlock;

extern PackedValueBlock gSelectionPackedValues;

PackedValueBlock *GetSelectionPackedValueBlock(void)
{
    return &gSelectionPackedValues;
}
