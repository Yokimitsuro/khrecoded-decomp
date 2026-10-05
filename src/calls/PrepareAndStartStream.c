#include "nitro/types.h"

extern char *data_0206084c;
s32 QueueTypedMessageWithHandle_0202cb38(u16 field1, u16 field2, s32 arg2);
int func_0202c44c(void);
void NNS_SndArcStrmStartPrepared(void *handle);

BOOL PrepareAndStartStream(int streamIndex, int streamId)
{
    u8 status;
    *(u8 *)(data_0206084c + 0xb47d8) = streamId;
    status = 0;
    QueueTypedMessageWithHandle_0202cb38(streamIndex, streamId, (s32)&status);
    func_0202c44c();
    /* Status 3 means preparation failed */
    if (status == 3)
        return FALSE;
    NNS_SndArcStrmStartPrepared(data_0206084c + 0xb44c0 + streamIndex * 4);
    return TRUE;
}

