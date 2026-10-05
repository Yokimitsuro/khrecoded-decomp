#include "nitro/types.h"

typedef struct ConnectState {
    u8 pad_00[0x79];
    u8 lowFlags : 4;
    u8 isHost : 1;
} ConnectState;

extern ConnectState *data_ov015_0207e964;
extern u32 GetPanelTransitionMode(void);
extern void PollPanelTransition(void);
extern void WH_Initialize(void);
extern unsigned int func_0202a9e4(unsigned int range);
extern void func_ov015_02072ee4(char nextState);

void HandleMatchTransition(void)
{
    switch (GetPanelTransitionMode()) {
    case 9:
    case 10:
        PollPanelTransition();
        break;
    case 1:
        if (data_ov015_0207e964->isHost) {
            break;
        }
        WH_Initialize();
        if (func_0202a9e4(100) < 50) {
            func_ov015_02072ee4(4);
        } else {
            func_ov015_02072ee4(5);
        }
        break;
    }
}
