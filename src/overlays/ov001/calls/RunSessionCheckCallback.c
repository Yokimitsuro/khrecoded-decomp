#include "nitro/types.h"

typedef struct Session {
    u8 pad_0000[0x2834];
    BOOL (*checkCallback)(void);
} Session;

extern Session *data_ov001_020a0480;

BOOL RunSessionCheckCallback(void)
{
    BOOL (*callback)(void) = data_ov001_020a0480->checkCallback;

    if (callback != NULL) {
        if (callback() == FALSE) {
            return TRUE;
        }
        return FALSE;
    }
    return TRUE;
}
