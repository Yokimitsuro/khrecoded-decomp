#include "nitro/types.h"

typedef struct Panel {
    u8 pad_00[0x54];
    u8 flags;
} Panel;

BOOL IsPanelFlagSet(Panel *panel, u8 bit)
{
    return (panel->flags & (1 << bit)) != 0;
}
