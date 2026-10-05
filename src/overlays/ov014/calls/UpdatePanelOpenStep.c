#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_0000[0xcf8a];
    s8 stateIndex;
    s8 closeRequested;
    s8 step;
} PanelState;

extern PanelState *data_ov014_0206f9a0;
extern void func_ov002_02062014(int mode);
extern void func_ov002_020664e4(int mode);
extern BOOL func_ov002_0206655c(void);
extern void func_ov014_0206d1c0(s8 nextState);

void UpdatePanelOpenStep(void)
{
    switch (data_ov014_0206f9a0->step) {
    case 0:
        func_ov002_02062014(1);
        data_ov014_0206f9a0->step = 1;
        break;
    case 1:
        func_ov002_020664e4(3);
        data_ov014_0206f9a0->step = 2;
        break;
    case 2:
        if (func_ov002_0206655c()) {
            func_ov014_0206d1c0(1);
        }
        break;
    }
}
