#include "nitro/types.h"

extern u32 data_ov030_020bcfa0;
extern void PXI_Init_0202a64c(u32 handle);
extern void BuildSelectionEntryList(void);
extern void SyncSelectionRecordFromSlotEntry(void);

void MobiClip_CloseDecoder(void)
{
    PXI_Init_0202a64c(data_ov030_020bcfa0);
    data_ov030_020bcfa0 = 0xffffffff;
    BuildSelectionEntryList();
    SyncSelectionRecordFromSlotEntry();
}
