#include "nitro/types.h"

typedef struct Panel {
    u8 pad_000[0x103];
    u8 formationType;
} Panel;

extern Panel *data_ov001_020a04e8;
extern u32 func_ov001_0207a8fc(Panel *panel);
extern void func_ov023_020b6db0(int formationType);

void Panel_SetFormationType(int formationType)
{
    Panel *panel;

    panel = data_ov001_020a04e8;
    panel->formationType = formationType;
    if (func_ov001_0207a8fc(panel) != 0) {
        func_ov023_020b6db0(formationType);
    }
}
