#include "nitro/types.h"

typedef struct MenuScene MenuScene;

extern MenuScene *data_ov097_020c2540;
extern void func_ov097_020c0efc(MenuScene *scene);
extern void ReleasePopupEntries(MenuScene *scene);
extern void func_ov097_020bff64(MenuScene *scene);
extern void ReleaseTextLayers_020bfae8(MenuScene *scene);
extern void FreeGraphicsResources_020bf84c(MenuScene *scene);
extern void FreeMessageBuffers_020bf70c(MenuScene *scene);
extern void SetStateFlagBits(u8 clearMask, u8 setBits);

void DestroyMenuScene_020bedc8(MenuScene *scene)
{
    func_ov097_020c0efc(scene);
    ReleasePopupEntries(scene);
    func_ov097_020bff64(scene);
    ReleaseTextLayers_020bfae8(scene);
    FreeGraphicsResources_020bf84c(scene);
    FreeMessageBuffers_020bf70c(scene);
    SetStateFlagBits(0, 5);
    data_ov097_020c2540 = NULL;
}
