#include "nitro/types.h"

typedef struct SceneGlobals {
    u32 unk_00;
    u8 *scene;
} SceneGlobals;

extern SceneGlobals data_ov001_020a04c4;

void *GetSceneTagTracker(void)
{
    return data_ov001_020a04c4.scene + 0x1c;
}
