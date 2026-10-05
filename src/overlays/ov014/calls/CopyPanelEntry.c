#include "nitro/types.h"

extern u32 data_ov014_0206f9a0;
extern void func_ov027_020b9380(u32 panel, u32 value, void *buffer, s32 flag);
extern u32 FindWidgetById(u32 panel, u32 value);
extern void func_ov027_020b91e8(u32 panel, u32 value, void *buffer, s32 flag);

void CopyPanelEntry(u32 entryId)
{
    u32 buffer[2];
    u32 slot;

    func_ov027_020b9380(data_ov014_0206f9a0 + 0x6514, entryId, buffer, 0);
    slot = FindWidgetById(data_ov014_0206f9a0 + 0x6514, 0);
    func_ov027_020b91e8(data_ov014_0206f9a0 + 0x6514, slot, buffer, 0);
}
