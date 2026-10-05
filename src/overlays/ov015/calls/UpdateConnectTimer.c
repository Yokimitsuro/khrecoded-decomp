#include "nitro/types.h"

typedef struct ConnectState {
    s8 mode;
    u8 pad_01;
    u8 timer;
    u8 pad_03[0x94 - 3];
    void *request;
} ConnectState;

extern ConnectState *data_ov015_0207e964;
extern u32 GetPanelTransitionMode(void);
extern void *func_ov015_02074e74(void *request, int size, int flags);

void UpdateConnectTimer(void)
{
    if ((u8)(s8)(data_ov015_0207e964->mode - 6) > 1) {
        return;
    }
    if (GetPanelTransitionMode() == 4) {
        if (func_ov015_02074e74(data_ov015_0207e964->request, 0x80, 0) != NULL) {
            data_ov015_0207e964->timer = 0x3c;
        }
    } else {
        data_ov015_0207e964->timer = 0;
    }
}
