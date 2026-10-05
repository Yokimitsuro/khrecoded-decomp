#include "nitro/types.h"

typedef struct PanelContext {
    u8 pad_00[4];
    u8 selection;
    u8 pad_05[0xe4 - 5];
    int pendingAction;
} PanelContext;

extern PanelContext *data_ov015_0207e960;
extern void func_ov002_020666c8(unsigned int value);

void ResetPanelSelection(void)
{
    data_ov015_0207e960->selection = 0;
    data_ov015_0207e960->pendingAction = 0;
    func_ov002_020666c8(0);
}
