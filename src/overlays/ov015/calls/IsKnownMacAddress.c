#include "nitro/types.h"

typedef struct {
    u8 pad_00[6];
    u8 knownMacs[30][6];
} WirelessContext;

extern BOOL MacAddressesEqual(u8 *macA, u8 *macB);
extern WirelessContext *data_ov015_0207e960;

BOOL IsKnownMacAddress(u8 *macAddress) {
    int i;

    i = 0;
    do {
        if (MacAddressesEqual(macAddress, data_ov015_0207e960->knownMacs[i]) == TRUE) {
            return TRUE;
        }
        i++;
    } while (i < 30);
    return FALSE;
}
