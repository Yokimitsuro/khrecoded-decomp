#include "nitro/types.h"

typedef struct SceneResources {
    u8 pad_00[0x04];
    u8 objectLists[3][0x34];
    u8 pad_a0[0x24];
    void *workBuffer;
    u8 pad_c8[0x08];
    u8 resourceNode[1];
} SceneResources;

extern void *func_ov039_020bc1ac(void);
extern void func_ov027_020b833c(void *elementSystem);
extern void FreePointerIfSet(void **ptr);
extern BOOL DestroyFndObjectList(void *container);
extern void ReleaseResourceAndDetach(void *object);
extern void NNS_GfdResetFrmTexVramState(void);
extern void NNS_GfdResetFrmPlttVramState(void);
extern void G3X_SetHOffset(u32 value);

void TeardownSceneResources(SceneResources *scene) {
    func_ov027_020b833c(func_ov039_020bc1ac());
    FreePointerIfSet(&scene->workBuffer);
    DestroyFndObjectList(scene->objectLists[0]);
    DestroyFndObjectList(scene->objectLists[1]);
    DestroyFndObjectList(scene->objectLists[2]);
    ReleaseResourceAndDetach(scene->resourceNode);
    NNS_GfdResetFrmTexVramState();
    NNS_GfdResetFrmPlttVramState();
    G3X_SetHOffset(0);
}
