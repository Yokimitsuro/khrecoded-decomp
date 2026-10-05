#include "nitro/types.h"

extern int data_ov070_020d8a3c[2][4];
extern BOOL func_ov070_020d8120(void *obj);
extern int GetClampedPaletteSlot(void);

int GetOv070PaletteEntry(void *obj)
{
    int row = func_ov070_020d8120(obj) != 0;

    return data_ov070_020d8a3c[row][GetClampedPaletteSlot()];
}
