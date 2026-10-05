#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct OverlaySelectionRecord {
    u8 overlaySet;
} OverlaySelectionRecord;

extern OverlaySelectionRecord *GetOverlaySelectionRecord(u32 selectionIndex);
extern VecFx32 data_ov021_020b4ec8[][9];

void GetSelectionSlotPosition(VecFx32 *out, u32 selectionIndex, int slot)
{
    OverlaySelectionRecord *record = GetOverlaySelectionRecord(selectionIndex);
    *out = data_ov021_020b4ec8[record->overlaySet][slot];
}
