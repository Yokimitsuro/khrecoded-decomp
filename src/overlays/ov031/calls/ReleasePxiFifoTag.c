#include "nitro/types.h"

extern u32 data_ov031_020bc7a0;
extern void PXI_Init_0202a64c(u32 tag);
extern void BuildSelectionEntryList(void);
extern void SyncSelectionRecordFromSlotEntry(void);

void ReleasePxiFifoTag(void)
{
    PXI_Init_0202a64c(data_ov031_020bc7a0);
    data_ov031_020bc7a0 = 0xffffffff;
    BuildSelectionEntryList();
    SyncSelectionRecordFromSlotEntry();
}
