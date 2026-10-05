#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0x75c];
    s32 motion;
    u8 pad_0760[0x944 - 0x760];
    s32 mode;
    u8 pad_0948[0x1708 - 0x948];
    s32 targetId;
} Actor;

extern Actor *data_ov059_020cffc4;

BOOL Actor_IsIdleWithoutTarget(void)
{
    BOOL result = FALSE;
    BOOL idle = TRUE;
    Actor *actor = data_ov059_020cffc4;

    if (actor->motion != 0 && actor->motion != 1) {
        idle = FALSE;
    }
    if (idle) {
        BOOL targeting = FALSE;
        if (!(actor->targetId == -1 || actor->mode == 7)) {
            targeting = TRUE;
        }
        if (!targeting) {
            result = TRUE;
        }
    }
    return result;
}
