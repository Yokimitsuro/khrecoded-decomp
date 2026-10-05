#include "nitro/types.h"

extern int func_ov015_0206c4f0(void);
extern void func_ov002_02062cb8(int nextMode);

void PollPanelOverlay15(void)
{
    switch (func_ov015_0206c4f0()) {
    case 1:
        func_ov002_02062cb8(0);
        break;
    case 2:
        func_ov002_02062cb8(0);
        break;
    }
}
