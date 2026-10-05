#include "nitro/types.h"

typedef struct MessagePathList {
    const char *paths[9];
} MessagePathList;

typedef struct FieldMessages {
    u8 pad_00[0xb8];
    void *containers[9];
} FieldMessages;

extern FieldMessages *data_ov001_020a04bc;
extern const MessagePathList gFieldMessagePaths;
extern void *Msg_OpenContainerAndReadHeader(const char *name, u32 mode, BOOL allocFromEnd);

void OpenFieldMessageContainers(void)
{
    FieldMessages *messages = data_ov001_020a04bc;
    MessagePathList list = gFieldMessagePaths;
    int i;

    for (i = 0; i < 9; i++) {
        messages->containers[i] = Msg_OpenContainerAndReadHeader(list.paths[i], 0x11, FALSE);
    }
}
