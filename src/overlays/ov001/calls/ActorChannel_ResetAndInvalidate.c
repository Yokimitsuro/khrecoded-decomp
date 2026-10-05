#include "nitro/types.h"

extern u8 *data_ov001_020a0514;
extern void ActorChannel_ResetFields(void);

void ActorChannel_ResetAndInvalidate(void)
{
    ActorChannel_ResetFields();
    *(u32 *)(data_ov001_020a0514 + 0x1e0) = 0xffffffff;
}
