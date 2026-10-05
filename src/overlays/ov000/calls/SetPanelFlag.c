#include "nitro/types.h"

typedef struct Panel {
    u8 pad_00[0x54];
    u8 flags;
} Panel;

void SetPanelFlag(Panel *panel, u8 bit, BOOL enable)
{
    if (enable) {
        panel->flags |= (u8)(1 << bit);
    } else {
        panel->flags &= (u8)~(1 << bit);
    }
}
