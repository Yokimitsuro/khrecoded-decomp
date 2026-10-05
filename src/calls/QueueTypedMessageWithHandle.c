#include "nitro/types.h"

extern void *AllocLoaderRequest(void);
extern void OS_SendMessage(void *queue, void *message, int flags);
extern int data_02060584;

typedef struct QueuedMessage {
    u8 pad_00[4];
    s32 type;
    u16 field1;
    u16 field2;
    s32 arg1;
    s32 arg2;
    u8 pad_14[0x28 - 0x14];
    s32 handle;
} QueuedMessage;

s32 QueueTypedMessageWithHandle(u16 field1, u16 field2, s32 arg1, s32 arg2) {
    QueuedMessage *msg = AllocLoaderRequest();

    if (msg == NULL) {
        return 0;
    }
    msg->type = 3;
    msg->field1 = field1;
    msg->field2 = field2;
    msg->arg1 = arg1;
    msg->arg2 = arg2;
    OS_SendMessage(&data_02060584, msg, 1);
    return msg->handle;
}
