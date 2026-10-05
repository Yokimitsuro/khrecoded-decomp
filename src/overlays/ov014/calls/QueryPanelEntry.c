#include "nitro/types.h"

extern u32 data_ov014_0206f9a0;
extern int func_ov027_020b9bb4(u32 panel, int entryId);

int QueryPanelEntry(int entryId)
{
    return func_ov027_020b9bb4(data_ov014_0206f9a0 + 0xc990, entryId);
}
