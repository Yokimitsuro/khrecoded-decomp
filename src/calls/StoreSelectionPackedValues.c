#include "nitro/types.h"

typedef struct PackedValueBlock {
    u32 savedByte;
    u16 values[3];
} PackedValueBlock;

typedef struct BitOffsetTable {
    u32 offsets[3];
} BitOffsetTable;

extern const BitOffsetTable data_02055a4c;
extern u16 data_020608d4[3];
extern PackedValueBlock gSelectionPackedValues;
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void WriteGlobalPackedBits(u32 bitOffset, u32 bitCount, u32 value);

void StoreSelectionPackedValues(const u16 *values)
{
    BitOffsetTable table = data_02055a4c;
    int i;

    MI_CpuCopy8(values, data_020608d4, sizeof(data_020608d4));
    for (i = 0; i < 3; i++) {
        WriteGlobalPackedBits(table.offsets[i], 0x10, gSelectionPackedValues.values[i]);
    }
}
