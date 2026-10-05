#include "nitro/types.h"

typedef struct Scene {
    u8 pad_000[0x5d0];
    u8 objectList[0xc];
} Scene;

typedef struct SceneGlobals {
    int allocEnabled;
    Scene *scene;
} SceneGlobals;

extern SceneGlobals data_ov001_020a04c4;
extern void NNS_FndRemoveListObject(void *list, void *object);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void FreeSceneListObject(void *object)
{
    SceneGlobals *globals = &data_ov001_020a04c4;

    globals->allocEnabled = 0;
    NNS_FndRemoveListObject(globals->scene->objectList, object);
    globals->allocEnabled = 1;
    NNSi_FndFreeFromDefaultHeap(object);
}
