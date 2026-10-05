#include "nitro/types.h"

extern u32 gMobiClipSourceHandle;
extern void PXI_Init_0202a64c(u32 handle);
extern void BuildSelectionEntryList(void);
extern void SyncSelectionRecordFromSlotEntry(void);

void MobiClip_CloseDecoder(void)
{
    PXI_Init_0202a64c(gMobiClipSourceHandle);
    gMobiClipSourceHandle = 0xffffffff;
    BuildSelectionEntryList();
    SyncSelectionRecordFromSlotEntry();
}
