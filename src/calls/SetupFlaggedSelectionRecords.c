#include "nitro/types.h"

typedef struct OverlaySelectionRecord {
    u8 overlaySet;
    u8 pad_001[0x12f];
    u16 unk_130;
    u8 pad_132[2];
    u8 unk_134;
    u8 unk_135;
} OverlaySelectionRecord;

extern u8 data_020608c8;

extern BOOL func_ov001_020645c8(u32 value);
extern void ApplySelectionStatScaling(u8 recordIndex, int kind);
extern void PackSelectionRecordEntry(u8 recordIndex, int kind, int flags);
extern OverlaySelectionRecord *GetOverlaySelectionRecord(u32 selectionIndex);

void SetupFlaggedSelectionRecords(void)
{
    data_020608c8 = 1;
    if (func_ov001_020645c8(0x3609)) {
        ApplySelectionStatScaling(data_020608c8, 2);
        PackSelectionRecordEntry(data_020608c8, 2, 0);
        data_020608c8++;
    }
    if (func_ov001_020645c8(0x360a)) {
        ApplySelectionStatScaling(data_020608c8, 1);
        PackSelectionRecordEntry(data_020608c8, 1, 0);
        data_020608c8++;
    }
    if (data_020608c8 > 2) {
        GetOverlaySelectionRecord(0)->unk_130 = 0xca;
        GetOverlaySelectionRecord(0)->unk_134 = 0;
        GetOverlaySelectionRecord(0)->unk_135 = 0;
    }
}
