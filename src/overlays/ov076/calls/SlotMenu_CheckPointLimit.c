#include "nitro/types.h"

typedef struct SlotMenu SlotMenu;

extern BOOL func_ov076_020c8b48(SlotMenu *menu);
extern void SlotMenu_ShowPointLimitWarning(SlotMenu *menu);

BOOL SlotMenu_CheckPointLimit(SlotMenu *menu, BOOL showWarning)
{
    if (!func_ov076_020c8b48(menu)) {
        if (showWarning) {
            SlotMenu_ShowPointLimitWarning(menu);
        }
        return FALSE;
    }
    return TRUE;
}
