#include "nitro/types.h"

extern s32 *data_ov001_020a04f4;
extern void func_ov001_0207e2c8(s32 *context);
extern void func_ov001_0207e2cc(s32 *context);

void DispatchByContextMode(void)
{
    s32 *context = data_ov001_020a04f4;

    switch (*context) {
    case 1:
        func_ov001_0207e2c8(context);
        break;
    case 2:
    case 3:
        func_ov001_0207e2cc(context);
        break;
    }
}
