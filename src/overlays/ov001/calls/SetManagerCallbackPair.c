#include "nitro/types.h"

typedef struct ActorManager {
    u8 pad_000[0x3F00];
    u32 field_3f00;
    u32 field_3f04;
} ActorManager;

extern ActorManager *data_ov001_020a0500;

void SetManagerCallbackPair(u32 value1, u32 value2)
{
    data_ov001_020a0500->field_3f00 = value1;
    data_ov001_020a0500->field_3f04 = value2;
}
