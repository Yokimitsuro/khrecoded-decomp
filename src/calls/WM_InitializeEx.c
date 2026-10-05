#include "nitro/types.h"

typedef struct {
    void *WM7;
    void *status;
    u8 pad_08[8];
    void *fifo7to9;
} WMArm9Buf;

extern int WmInit(int wmSysBuf, int dmaNo);
extern void SetCommandArg(int idx, int value);
extern void RegisterPxiPreSleepCallback(void);
extern int func_02011050(void);
extern int WMi_SendCommand(int id, u16 paramNum, ...);

int WM_InitializeEx(int wmSysBuf, int callback, int dmaNo, int miscFlags)
{
    int result;
    WMArm9Buf *wm9buf;

    result = WmInit(wmSysBuf, dmaNo);
    if (result != 0) {
        return result;
    }

    SetCommandArg(0, callback);
    RegisterPxiPreSleepCallback();

    wm9buf = (WMArm9Buf *)func_02011050();
    result = WMi_SendCommand(0, 4, (int)wm9buf->WM7, (int)wm9buf->status, (int)wm9buf->fifo7to9, miscFlags);
    if (result == 0) {
        result = 2;
    }
    return result;
}
