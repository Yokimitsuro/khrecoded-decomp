#include "nitro/types.h"

typedef struct OverlaySelectionRecord {
    u8 overlaySet;
    u8 pad_001[0xf];
    u8 unk_010;
} OverlaySelectionRecord;

typedef struct SelectionState {
    u8 recordCount;
    u8 pad_01[3];
    int taggedCount;
    u32 savedByte;
} SelectionState;

typedef struct PackedValueBlock {
    u32 savedByte;
    u16 values[3];
} PackedValueBlock;

typedef struct BitOffsetTable {
    u32 offsets[3];
} BitOffsetTable;

extern const BitOffsetTable data_02055a40;
extern SelectionState data_020608c8;
extern PackedValueBlock gSelectionPackedValues;
extern OverlaySelectionRecord *GetOverlaySelectionRecord(u32 selectionIndex);
extern u32 ReadGlobalPackedBits(u32 bitOffset, u32 bitCount);

void LoadSelectionPackedValues(void)
{
    BitOffsetTable table = data_02055a40;
    int i;

    i = 0;
    data_020608c8.savedByte = GetOverlaySelectionRecord(0)->unk_010;
    do {
        gSelectionPackedValues.values[i] = ReadGlobalPackedBits(table.offsets[i], 0x10);
        i++;
    } while (i < 3);
}
