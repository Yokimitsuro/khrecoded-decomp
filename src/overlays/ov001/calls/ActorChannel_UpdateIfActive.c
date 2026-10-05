#include "nitro/types.h"

typedef struct ChannelContext {
    u8 pad_000[0x1dc];
    u16 active;
} ChannelContext;

extern ChannelContext *data_ov001_020a0514;
extern int func_ov001_0208b7a8(void);

void ActorChannel_UpdateIfActive(void)
{
    if (data_ov001_020a0514->active != 0) {
        func_ov001_0208b7a8();
    }
}
