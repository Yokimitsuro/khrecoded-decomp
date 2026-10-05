#include "nitro/types.h"

typedef struct SubModeState {
    s32 mode;
} SubModeState;

extern SubModeState *data_ov021_020b56c0;

extern void Camera_StartTargetView(int first, int second, int third);
extern void GetPanelViewEx(int first, int second, int third);

void ForwardSubModeEvent(int first, int second, int third)
{
    switch (data_ov021_020b56c0->mode) {
    case 0:
        Camera_StartTargetView(first, second, third);
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        GetPanelViewEx(first, second, third);
        break;
    }
}
