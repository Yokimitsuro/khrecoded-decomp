#include "nitro/types.h"

typedef struct ActorManager {
    u8 pad_000[0x140];
    u8 pad_140[0x628];
    u32 field_768;
} ActorManager;

extern ActorManager *data_ov001_020a0500;
extern void MarkPendingActionIfTargetSet(void *dst);

u32 GetManagerStateFlag(void)
{
    MarkPendingActionIfTargetSet((u8 *)data_ov001_020a0500 + 0x140);
    return data_ov001_020a0500->field_768;
}
