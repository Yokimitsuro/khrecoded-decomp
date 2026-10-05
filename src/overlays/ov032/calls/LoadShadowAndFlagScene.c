#include "nitro/types.h"

typedef struct {
    u8 pad_00[6];
    u16 flags;
    s8 mode;
} SceneState;

typedef struct {
    u8 *context;
    SceneState *scene;
} Ov032Globals;

extern Ov032Globals data_ov032_020c0080;
extern s32 RestoreSessionActors(void);
extern void ObjectManager_LoadShadowModel(void);

s32 LoadShadowAndFlagScene(void) {
    if (RestoreSessionActors() == 1 && data_ov032_020c0080.scene->mode != 3) {
        data_ov032_020c0080.scene->mode = 0;
    }
    ObjectManager_LoadShadowModel();
    data_ov032_020c0080.scene->flags |= 0x8000;
    return 2;
}
