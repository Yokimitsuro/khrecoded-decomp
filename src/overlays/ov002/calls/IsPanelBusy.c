#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x11];
    u8 slotCTriggered : 1;
    u8 slotDTriggered : 1;
    u8 busy : 1;
    u8 unk_11_3 : 5;
} PanelState;

extern PanelState *data_ov002_0206c460;

u32 IsPanelBusy(void)
{
    return data_ov002_0206c460->busy;
}
