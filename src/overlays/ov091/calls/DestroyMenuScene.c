#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xca08];
    void *task;
} MenuScene;

extern void func_ov091_020c27ec(void *task);
extern void ReleaseListRecords(MenuScene *scene);
extern void ReleaseListPanels(MenuScene *scene);
extern void ReleaseTextLayers(MenuScene *scene);
extern void FreeGraphicsResources(MenuScene *scene);
extern void FreeMessageBuffers(MenuScene *scene);
extern void func_02050a58(void);
extern void SetStateFlagBits(u8 clearMask, u8 setBits);

void DestroyMenuScene(MenuScene *scene)
{
    func_ov091_020c27ec(scene->task);
    ReleaseListRecords(scene);
    ReleaseListPanels(scene);
    ReleaseTextLayers(scene);
    FreeGraphicsResources(scene);
    FreeMessageBuffers(scene);
    func_02050a58();
    SetStateFlagBits(0, 5);
}
