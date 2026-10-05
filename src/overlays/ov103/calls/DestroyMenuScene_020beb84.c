#include "nitro/types.h"

typedef struct MenuScene MenuScene;

extern void ReleaseSlotPool_020bf66c(MenuScene *scene);
extern void FreeTextLayers(MenuScene *scene);
extern void FreeGraphicsResources_020bf094(MenuScene *scene);
extern void FreeArchiveFiles(MenuScene *scene);
extern void SetStateFlagBits(u8 clearMask, u8 setBits);

void DestroyMenuScene_020beb84(MenuScene *scene)
{
    ReleaseSlotPool_020bf66c(scene);
    FreeTextLayers(scene);
    FreeGraphicsResources_020bf094(scene);
    FreeArchiveFiles(scene);
    SetStateFlagBits(0, 5);
}
