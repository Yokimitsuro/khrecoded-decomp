#include "nitro/types.h"

typedef struct WirelessHelper {
    u8 pad_00[0x20];
    int errorCode;
    u8 pad_24[0x50 - 0x24];
    int sysState;
} WirelessHelper;

extern WirelessHelper data_ov015_0207e980;

void WH_SetError(int code)
{
    if ((u32)(data_ov015_0207e980.sysState - 9) > 1) {
        data_ov015_0207e980.errorCode = code;
    }
}
