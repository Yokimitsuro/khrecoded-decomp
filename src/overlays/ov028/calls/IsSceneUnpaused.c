#include "nitro/types.h"

typedef struct {
    u8 pad_00[6];
    u16 flags;
} SceneState;

extern SceneState *data_ov028_020bb3a0;

BOOL IsSceneUnpaused(void) {
    BOOL result = TRUE;

    if (data_ov028_020bb3a0->flags & 0x10) {
        result = FALSE;
    }
    return result;
}
