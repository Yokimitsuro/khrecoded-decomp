#include "nitro/types.h"

typedef struct SubModeState {
    s32 mode;
} SubModeState;

extern SubModeState *data_ov021_020b56c0;

extern void Camera_SetFrozen(BOOL frozen);
extern void func_ov043_020bcb34(BOOL frozen);
extern void SetPanelFlagBit1(BOOL frozen);

void SetSubModeFrozen(BOOL frozen)
{
    switch (data_ov021_020b56c0->mode) {
    case 0:
        Camera_SetFrozen(frozen);
        break;
    case 1:
        break;
    case 2:
        func_ov043_020bcb34(frozen);
        break;
    case 3:
        SetPanelFlagBit1(frozen);
        break;
    }
}
