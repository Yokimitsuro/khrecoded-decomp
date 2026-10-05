#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x18];
    s64 startTick;
} CardThreadState;

extern CardThreadState data_0205fe00;

s64 GetCardThreadStartTick(void)
{
    return data_0205fe00.startTick;
}
