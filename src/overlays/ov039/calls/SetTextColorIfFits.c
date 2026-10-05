#include "nitro/types.h"

extern int data_ov039_020bea20;
extern void Obj_SetField14(int *object, int value);
extern int func_0200191c(int *object, int text, int flags);

BOOL SetTextColorIfFits(int *object, int limit, int text)
{
    int base = data_ov039_020bea20;
    BOOL fits;

    Obj_SetField14(object, base + 0xca90);
    fits = func_0200191c(object, text, 0) < limit;
    if (!fits) {
        Obj_SetField14(object, base + 0xcaa8);
    }
    return fits;
}
