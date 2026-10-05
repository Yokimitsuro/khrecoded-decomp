#include "nitro/types.h"

typedef struct PanelContext {
    s8 screenMode;
} PanelContext;

extern PanelContext *data_ov015_0207e960;
extern void AnimateSubBg1Screen(void);
extern void func_ov015_0206fcd8(void);
extern void func_ov015_0206fe44(void);

void AnimatePanelBackground(void)
{
    switch (data_ov015_0207e960->screenMode) {
    case 0:
    case 1:
    case 7:
        AnimateSubBg1Screen();
        break;
    case 2:
    case 3:
    case 6:
        func_ov015_0206fcd8();
        break;
    case 5:
        func_ov015_0206fe44();
        break;
    case 4:
        break;
    }
}
