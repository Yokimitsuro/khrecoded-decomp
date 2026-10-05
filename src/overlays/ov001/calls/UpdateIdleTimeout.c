#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldResources {
    u8 pad_00[0x28];
    u16 flags;
    u8 pad_2a[0x6a];
    s32 idleEnabled;
    fx32 idleTimer;
} FieldResources;

extern FieldResources *data_ov001_020a04bc;

extern BOOL func_ov001_020642a0(void);

BOOL UpdateIdleTimeout(void)
{
    FieldResources *resources = data_ov001_020a04bc;
    BOOL expired = FALSE;

    if (resources->idleEnabled != 0) {
        if (!func_ov001_020642a0()) {
            if (resources->idleTimer >= 0x3c000) {
                expired = TRUE;
            } else {
                resources->idleTimer += 0x1000;
            }
        } else {
            resources->idleTimer = 0;
        }
    }
    if ((resources->flags & 0x10) > 0) {
        expired = TRUE;
    }
    return expired;
}
