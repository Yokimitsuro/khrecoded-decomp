#include "nitro/types.h"

typedef struct SubModeState {
    s32 mode;
} SubModeState;

extern SubModeState *data_ov021_020b56c0;

extern void func_ov046_020c1614(void *arg);
extern void GetPanelView(void *arg);

void CopySubModeState(void *arg)
{
    switch (data_ov021_020b56c0->mode) {
    case 0:
        func_ov046_020c1614(arg);
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        GetPanelView(arg);
        break;
    }
}
