#include "nitro/types.h"

extern int data_ov032_020c0080[];

BOOL IsContextFlag10Clear(void)
{
    BOOL result = TRUE;
    if (*(u16 *)(data_ov032_020c0080[1] + 6) & 0x10) {
        result = FALSE;
    }
    return result;
}
