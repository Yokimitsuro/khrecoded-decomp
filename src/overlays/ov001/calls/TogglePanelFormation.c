#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x103];
    u8 formationType;
} PanelScene;

extern PanelScene *data_ov001_020a04e8;

extern BOOL func_ov001_0207a8fc(PanelScene *panel);
extern void ApplyFormationSlots(int formationType);

void TogglePanelFormation(void)
{
    PanelScene *panel = data_ov001_020a04e8;

    if (panel->formationType == 1) {
        panel->formationType = 2;
    } else {
        panel->formationType = 1;
    }
    if (func_ov001_0207a8fc(panel)) {
        ApplyFormationSlots(panel->formationType);
    }
}
