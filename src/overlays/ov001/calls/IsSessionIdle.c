#include "nitro/types.h"

typedef struct SessionFlags {
    u32 unk_0 : 6;
    u32 resumePending : 1;
    u32 unk_7 : 5;
    u32 promptOpen : 1;
    u32 unk_13 : 19;
} SessionFlags;

typedef struct Session {
    u8 pad_0000[0x20];
    u32 displayFlags;
    u8 pad_0024[0x214 - 0x24];
    SessionFlags flags;
    u8 pad_0218[0x2738 - 0x218];
    s8 inputFlags;
    u8 pad_2739[0x2744 - 0x2739];
    s8 pendingCount;
    u8 pad_2745[0x27f8 - 0x2745];
    s8 modeState;
} Session;

extern Session *data_ov001_020a0480;
extern BOOL IsScreenModeIdle(void);
extern BOOL func_ov001_020645c8(u32 value);
extern BOOL IsFirstEntryFlagSet(void);
extern BOOL func_ov001_020642a0(void);

BOOL IsSessionIdle(void) {
    Session *session = data_ov001_020a0480;
    if (!IsScreenModeIdle()) {
        return FALSE;
    }
    if (func_ov001_020645c8(0x35e5) || session->flags.promptOpen || session->flags.resumePending) {
        return FALSE;
    }
    if (session->inputFlags & 0x80) {
        return FALSE;
    }
    if (session->displayFlags & 0x10) {
        return FALSE;
    }
    if (IsFirstEntryFlagSet() || session->pendingCount > 0) {
        return FALSE;
    }
    if (func_ov001_020642a0()) {
        return FALSE;
    }
    if (data_ov001_020a0480->modeState != 1) {
        return TRUE;
    }
    return FALSE;
}
