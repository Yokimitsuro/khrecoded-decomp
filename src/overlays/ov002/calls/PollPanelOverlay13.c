#include "nitro/types.h"

extern int func_ov013_0206c7e8(void);
extern void func_ov002_02062cb8(int nextMode);

void PollPanelOverlay13(void)
{
    switch (func_ov013_0206c7e8()) {
    case 1:
        func_ov002_02062cb8(0);
        break;
    case 2:
        func_ov002_02062cb8(4);
        break;
    }
}
