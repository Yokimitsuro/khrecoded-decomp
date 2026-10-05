#include "nitro/types.h"

typedef struct SessionFlags {
    u32 unk_0 : 6;
    u32 bit6 : 1;
    u32 bit7 : 1;
    u32 unk_8 : 24;
} SessionFlags;

typedef struct Session {
    u8 pad_0000[0x214];
    SessionFlags flags;
    u8 pad_0218[0x281c - 0x218];
    BOOL (*pollCallback)(void);
} Session;

extern Session *data_ov001_020a0480;

s32 WaitSessionPollAndClearFlags(void) {
    Session *session = data_ov001_020a0480;
    if (session->pollCallback != NULL && session->pollCallback()) {
        session->flags.bit7 = 0;
        session->flags.bit6 = 0;
        return 6;
    }
    return -1;
}
