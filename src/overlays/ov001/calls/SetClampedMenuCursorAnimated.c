#include "nitro/types.h"

extern void SetClampedMenuCursor(u32 cursor, int animate);

void SetClampedMenuCursorAnimated(u16 cursor)
{
    SetClampedMenuCursor(cursor, 7);
}
