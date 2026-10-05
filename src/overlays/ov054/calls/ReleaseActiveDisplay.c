#include "nitro/types.h"

typedef struct DisplayState {
    u8 pad_000[0x9ac];
    u64 flags;
} DisplayState;

typedef struct SceneGlobals {
    u8 pad_0000[0x125c];
    DisplayState *activeDisplay;
} SceneGlobals;

typedef struct SceneObject SceneObject;
struct SceneObject {
    u8 pad_000[0x1f8];
    void (*onEvent)(SceneObject *scene, int arg, int value);
    u8 pad_1fc[0x768 - 0x1fc];
    int isActive;
    u8 pad_76c[0x10ec - 0x76c];
    void (*setMode)(SceneObject *scene, int mode);
};

extern SceneGlobals *data_ov054_020d3720;

void ReleaseActiveDisplay(SceneObject *scene)
{
    SceneGlobals *globals = data_ov054_020d3720;
    DisplayState *display;
    if (scene->isActive == 0) {
        return;
    }
    display = globals->activeDisplay;
    display->flags |= 0x800000;
    globals->activeDisplay = NULL;
    scene->setMode(scene, 1);
    if (scene->onEvent == NULL) {
        return;
    }
    scene->onEvent(scene, 0, -1);
}
