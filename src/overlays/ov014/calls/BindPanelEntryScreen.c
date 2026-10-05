#include "nitro/types.h"

extern u32 data_ov014_0206f9a0;
extern void *G2S_GetBG0ScrPtr(void);
extern void func_ov027_020b9b38(u32 panel, u32 entryId, void *scrPtr);

void BindPanelEntryScreen(u32 entryId)
{
    void *scrPtr = G2S_GetBG0ScrPtr();
    func_ov027_020b9b38(data_ov014_0206f9a0 + 0xc990, entryId, scrPtr);
}
