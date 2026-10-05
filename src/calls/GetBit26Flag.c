#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    u8 *data;
} MainDataHolder_0205fe00;

extern MainDataHolder_0205fe00 data_0205fe00;

u32 GetBit26Flag(void)
{
    return (*(u32 *)(data_0205fe00.data + 0x277c) << 5) >> 0x1f;
}
