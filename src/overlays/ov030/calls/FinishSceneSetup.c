#include "nitro/types.h"

typedef struct {
    u8 pad_00[6];
    u16 flags;
    s8 mode;
} SceneState;

extern SceneState *data_ov030_020bd020;

extern int func_ov001_02063404(void);
extern void ObjectManager_LoadShadowModel(void);

int FinishSceneSetup(void) {
    if (func_ov001_02063404() == 1 && data_ov030_020bd020->mode != 3) {
        data_ov030_020bd020->mode = 0;
    }
    ObjectManager_LoadShadowModel();
    data_ov030_020bd020->flags |= 0x8000;
    return 2;
}
