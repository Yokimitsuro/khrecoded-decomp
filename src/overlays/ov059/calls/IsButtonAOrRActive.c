#include "nitro/types.h"

#define PAD_BUTTON_A 0x0001
#define PAD_BUTTON_R 0x0100

extern BOOL HasFlagsAt0xe(void *inputState, u16 buttonMask);

BOOL IsButtonAOrRActive(void *inputState)
{
    if (HasFlagsAt0xe(inputState, PAD_BUTTON_A) ||
        HasFlagsAt0xe(inputState, PAD_BUTTON_R)) {
        return TRUE;
    }
    return FALSE;
}
