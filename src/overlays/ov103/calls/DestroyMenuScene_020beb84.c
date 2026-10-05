#include "nitro/types.h"

typedef struct MenuScene MenuScene;

extern void ReleaseSlotPool_020bf66c(MenuScene *scene);
extern void func_ov103_020bf34c(MenuScene *scene);
extern void FreeGraphicsResources_020bf094(MenuScene *scene);
extern void FreeArchiveFiles(MenuScene *scene);
extern void SetStateFlagBits(u8 clearMask, u8 setBits);

void DestroyMenuScene_020beb84(MenuScene *scene)
{
    ReleaseSlotPool_020bf66c(scene);
    func_ov103_020bf34c(scene);
    FreeGraphicsResources_020bf094(scene);
    FreeArchiveFiles(scene);
    SetStateFlagBits(0, 5);
}
