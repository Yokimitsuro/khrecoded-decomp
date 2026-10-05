#include "nitro/types.h"

extern const u32 data_ov072_020d9bfc[2][4];
extern BOOL IsObjectType111(void *object);
extern int GetClampedPaletteSlot(void);

u32 GetObjectPaletteValue(void *object)
{
    BOOL isType = IsObjectType111(object) != 0;

    return data_ov072_020d9bfc[isType][GetClampedPaletteSlot()];
}
