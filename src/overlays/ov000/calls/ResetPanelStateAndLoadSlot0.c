#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x48];
    u32 field_48;
    u32 field_4c;
    u8 pad_50[0x6688 - 0x50];
    u32 field_6688;
} Panel;

extern void StartCardWriteFromSlot(u8 slot);

void ResetPanelStateAndLoadSlot0(Panel *panel)
{
    panel->field_4c = 0;
    panel->field_48 = 0;
    panel->field_6688 = 0;
    StartCardWriteFromSlot(0);
}
