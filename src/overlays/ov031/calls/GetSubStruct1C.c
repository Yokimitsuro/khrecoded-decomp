#include "nitro/types.h"

extern u32 data_ov031_020bc820;

int GetSubStruct1C(void)
{
    if (data_ov031_020bc820 != 0) {
        return data_ov031_020bc820 + 0x1c;
    }
    return 0;
}
