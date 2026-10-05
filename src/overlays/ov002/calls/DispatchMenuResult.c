#include "nitro/types.h"

extern int UpdateMenuContext(void);
extern void func_ov002_02062cb8(int mode);

void DispatchMenuResult(void)
{
    switch (UpdateMenuContext()) {
    case 0:
        break;
    case 1:
        func_ov002_02062cb8(1);
        break;
    case 2:
        func_ov002_02062cb8(2);
        break;
    case 3:
        func_ov002_02062cb8(3);
        break;
    case 4:
        break;
    case 5:
        func_ov002_02062cb8(5);
        break;
    case 6:
        func_ov002_02062cb8(6);
        break;
    }
}
