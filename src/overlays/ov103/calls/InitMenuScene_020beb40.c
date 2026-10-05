#include "nitro/types.h"

typedef struct {
    void *fileData;
    u8 pad_04[0xc];
} GraphicsResource;

typedef struct MenuScene {
    u8 pad_000[0x134];
    GraphicsResource resources[4];
} MenuScene;

extern MenuScene *data_ov103_020c0720;
extern void func_ov103_020bed5c(void);
extern void SetStateFlagBits(u8 clearMask, u8 setBits);
extern void SetScenePhase(int state, MenuScene *scene);

BOOL InitMenuScene_020beb40(MenuScene *scene)
{
    data_ov103_020c0720 = scene;
    scene->resources[3].fileData = NULL;
    func_ov103_020bed5c();
    SetStateFlagBits(5, 0);
    SetScenePhase(1, scene);
    return TRUE;
}
