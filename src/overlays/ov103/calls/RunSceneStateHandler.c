#include "nitro/types.h"

typedef struct MenuScene MenuScene;
typedef void (*SceneStateHandler)(MenuScene *scene);

extern int func_ov103_020c032c(MenuScene *scene);
extern SceneStateHandler data_ov103_020c049c[];

void RunSceneStateHandler(MenuScene *scene)
{
    SceneStateHandler handler = data_ov103_020c049c[func_ov103_020c032c(scene)];

    if (handler != NULL) {
        handler(scene);
    }
}
