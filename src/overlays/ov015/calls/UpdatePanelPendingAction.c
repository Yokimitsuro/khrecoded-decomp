#include "nitro/types.h"

typedef struct PanelContext {
    u8 pad_00[0xe4];
    int pendingAction;
} PanelContext;

extern PanelContext *data_ov015_0207e960;
extern void func_ov002_02062014(int value);
extern void func_ov002_020664e4(int mode);
extern u32 func_ov002_0206655c(void);
extern void func_ov015_02070af8(char nextState);

void UpdatePanelPendingAction(void)
{
    switch (data_ov015_0207e960->pendingAction) {
    case 0:
        func_ov002_02062014(1);
        data_ov015_0207e960->pendingAction = 10;
        break;
    case 10:
        func_ov002_020664e4(3);
        data_ov015_0207e960->pendingAction = 20;
        break;
    case 20:
        if (func_ov002_0206655c() != 0) {
            func_ov015_02070af8(3);
        }
        break;
    }
}
