#include "nitro/types.h"

extern int data_ov071_020d969c[2][4];
extern BOOL func_ov071_020d8120(void *obj);
extern int GetClampedPaletteSlot(void);

int GetOv071PaletteEntry(void *obj)
{
    int row = func_ov071_020d8120(obj) != 0;

    return data_ov071_020d969c[row][GetClampedPaletteSlot()];
}
