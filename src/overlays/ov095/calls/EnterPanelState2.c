#include "nitro/types.h"

typedef struct {
    u8 pad[0x11104];
    int state;
} PanelWork;

extern void SetPanelMode_020c1210(int mode, PanelWork *work);

void EnterPanelState2(PanelWork *work) {
    work->state = 2;
    SetPanelMode_020c1210(2, work);
}
