#include "nitro/types.h"

typedef struct ChannelContext {
    u8 pad_000[0x1dc];
    u16 active;
} ChannelContext;

extern ChannelContext *data_ov001_020a0514;
extern int UpdateFieldCamera(void);

void ActorChannel_UpdateIfActive(void)
{
    if (data_ov001_020a0514->active != 0) {
        UpdateFieldCamera();
    }
}
