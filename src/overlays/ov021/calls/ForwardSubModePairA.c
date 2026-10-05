#include "nitro/types.h"

typedef struct SubModeState {
    s32 mode;
} SubModeState;

extern SubModeState *data_ov021_020b56c0;

extern void Camera_ChangeViewMode(int first, int second);
extern void SetCameraModeValue(int first, int second);
extern void func_ov044_020d0580(int first, int second);

void ForwardSubModePairA(int first, int second)
{
    switch (data_ov021_020b56c0->mode) {
    case 0:
        Camera_ChangeViewMode(first, second);
        break;
    case 1:
        break;
    case 2:
        SetCameraModeValue(first, second);
        break;
    case 3:
        func_ov044_020d0580(first, second);
        break;
    }
}
