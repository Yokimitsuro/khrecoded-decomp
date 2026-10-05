#include "nitro/types.h"

extern s32 UpdateMenuSelection(void);

u32 UpdateMenuSelectionAndReturnState7(void)
{
    UpdateMenuSelection();
    return 7;
}
