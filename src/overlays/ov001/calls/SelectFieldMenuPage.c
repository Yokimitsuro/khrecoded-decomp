#include "nitro/types.h"

typedef struct Scene {
    u8 pad_000[0x480];
    u32 unk0 : 16;
    u32 altMenu : 1;
    u32 unk17 : 15;
} Scene;

typedef struct SceneGlobals {
    int allocEnabled;
    Scene *scene;
} SceneGlobals;

extern SceneGlobals data_ov001_020a04c4;
extern void func_ov001_020781a4(int page);

void SelectFieldMenuPage(int page)
{
    if (data_ov001_020a04c4.scene->altMenu == 1 && (page == 0 || page == 7)) {
        page = 0xd;
    }
    func_ov001_020781a4(page);
}
