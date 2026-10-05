#include "nitro/types.h"

typedef struct SubModeState {
    s32 mode;
} SubModeState;

extern SubModeState *data_ov021_020b56c0;

extern void Camera_ApplyStateIfStandard(int value);
extern void func_ov044_020d0ba4(int value);

void ForwardSubModeValue(int value)
{
    switch (data_ov021_020b56c0->mode) {
    case 0:
        Camera_ApplyStateIfStandard(value);
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        func_ov044_020d0ba4(value);
        break;
    }
}
