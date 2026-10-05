#include "nitro/types.h"

typedef struct ActorManager {
    u8 pad_000[0x3F1C];
    u32 field_3f1c;
} ActorManager;

extern ActorManager *data_ov001_020a0500;

u32 GetManagerUnknownValue(void)
{
    return data_ov001_020a0500->field_3f1c;
}
