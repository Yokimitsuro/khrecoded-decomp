#include "nitro/types.h"

typedef struct SessionInfo {
    u16 partnerId;
    u8 pad_02[0xf];
    u8 flags;
} SessionInfo;

extern SessionInfo *data_ov001_020a0498;

BOOL IsSessionLinked(void)
{
    SessionInfo *session = data_ov001_020a0498;
    BOOL linked = TRUE;

    if (!(session->flags & 1) || session->partnerId == 0xffff) {
        linked = FALSE;
    }
    return linked;
}
