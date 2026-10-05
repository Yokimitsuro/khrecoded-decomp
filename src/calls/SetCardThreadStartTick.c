#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x18];
    s64 startTick;
} CardThreadState;

extern CardThreadState data_0205fe00;
extern s64 OS_GetTick(void);

void SetCardThreadStartTick(void)
{
    data_0205fe00.startTick = OS_GetTick();
}
