#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x10];
    u8 disabled : 1;
    u8 unk_10_1 : 7;
} PanelState;

extern PanelState *data_ov002_0206c460;

extern void func_0204d808(int new_value);
extern void SetPendingScene(s32 pendId, s32 pendArg);

void ClosePanelAndQueueScene(void)
{
    func_0204d808(0x14);
    SetPendingScene(1, -2);
    data_ov002_0206c460->disabled = 1;
}
