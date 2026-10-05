#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_0000[0xcf8a];
    s8 stateIndex;
    s8 closeRequested;
    s8 step;
} PanelState;

extern PanelState *data_ov014_0206f9a0;
extern void func_ov002_020664f4(int mode);
extern BOOL func_ov002_0206655c(void);

void UpdatePanelCloseStep(void)
{
    switch (data_ov014_0206f9a0->step) {
    case 0:
        data_ov014_0206f9a0->step = 1;
        break;
    case 1:
        func_ov002_020664f4(3);
        data_ov014_0206f9a0->step = 2;
        break;
    case 2:
        if (func_ov002_0206655c()) {
            data_ov014_0206f9a0->closeRequested = 1;
            data_ov014_0206f9a0->step = -1;
        }
        break;
    }
}
