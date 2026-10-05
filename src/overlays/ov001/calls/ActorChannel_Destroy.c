#include "nitro/types.h"

extern u8 *data_ov001_020a0514;
extern void Obj_ReleaseIfSet(void *channel);

void ActorChannel_Destroy(void)
{
    Obj_ReleaseIfSet(data_ov001_020a0514 + 0x140);
    data_ov001_020a0514 = 0;
}
