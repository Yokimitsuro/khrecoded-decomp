#include "nitro/types.h"

typedef struct {
    u8 overlaySet;
    u8 pad_001[0x1d];
    u8 unk_1E;
} OverlaySelectionRecord;

extern OverlaySelectionRecord *GetOverlaySelectionRecord(u32 selectionIndex);

u8 GetPrimarySelectionByte1E(void)
{
    return GetOverlaySelectionRecord(0)->unk_1E;
}
