#include "nitro/types.h"

typedef struct {
    u8 overlaySet;
    u8 pad_001[0xf];
    u8 packedEntry[0x1c];
} OverlaySelectionRecord;

extern OverlaySelectionRecord *GetOverlaySelectionRecord(u32 selectionIndex);
extern void PackNamedRecordEntry(u8 *out, int index, int nameId);

void PackSelectionRecordEntry(u32 selectionIndex, int nameId, int entryIndex)
{
    PackNamedRecordEntry(GetOverlaySelectionRecord(selectionIndex)->packedEntry, entryIndex, nameId);
}
