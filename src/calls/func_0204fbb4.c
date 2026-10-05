#include "nitro/types.h"

typedef struct {
    u8 overlaySet;
    u8 pad_001[0x13b];
    u8 unk_13C[8];
} OverlaySelectionRecord;

extern void AcquireMapLayout(int reload, int discardCached);
extern OverlaySelectionRecord *GetOverlaySelectionRecord(u32 selectionIndex);
extern void BuildAbilityTable(void *list);
extern void func_02050a58(void);

void func_0204fbb4(void)
{
    AcquireMapLayout(0, 0);
    BuildAbilityTable(GetOverlaySelectionRecord(0)->unk_13C);
    func_02050a58();
}
