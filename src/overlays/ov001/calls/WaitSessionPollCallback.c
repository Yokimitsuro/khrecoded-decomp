#include "nitro/types.h"

typedef struct Session {
    u8 pad_0000[0x281c];
    BOOL (*pollCallback)(void);
} Session;

extern Session *data_ov001_020a0480;

s32 WaitSessionPollCallback(void) {
    Session *session = data_ov001_020a0480;
    if (session->pollCallback != NULL && !session->pollCallback()) {
        return -1;
    }
    return 11;
}
