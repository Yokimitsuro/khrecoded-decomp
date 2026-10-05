#include "nitro/types.h"

extern u8 *data_ov001_020a0514;

void *ActorChannel_SelectBuffer(void)
{
    u8 *result = data_ov001_020a0514;
    if (*(s32 *)(data_ov001_020a0514 + 0x1ec) != 0) {
        result = data_ov001_020a0514 + 0xa0;
    }
    return result;
}
