#include "src/calls/scene_control.h"

extern void *data_0206039c;
extern u8 gSceneControllerStorage[];

extern int  func_0202a734(void *obj);
extern void func_02029fac(int, int);
extern void ResetCallbackTable(void);
extern void func_0202a104(void *);
extern void func_02029f8c(int module, int overlayId);
extern void *func_0202a45c(void *classDesc, int arg);
extern void StoreWord0(void *obj, int);

int AdvancePendingScene(void) {
    SceneController *scene = (SceneController *)gSceneControllerStorage;

    if (*(void **)&gSceneController != 0) {
        if (func_0202a734(scene->object) != 0) {
            if (scene->entry->overlayId != -1) {
                func_02029fac(0, scene->entry->overlayId);
            }
            ResetCallbackTable();
            func_0202a104(data_0206039c);
            scene->object = 0;
            scene->currentId = 0;
        }
    }

    if (scene->object == 0) {
        int id = scene->pendingId;
        if (id != 0) {
            int ov = gSceneTable[id].overlayId;
            SceneEntry *ent = &gSceneTable[id];
            if (ov != -1) {
                func_02029f8c(0, ov);
            }
            {
                void *obj = func_0202a45c(ent->classDesc, scene->pendingArg);
                scene->object = obj;
                scene->entry = ent;
                StoreWord0(obj, 1);
            }
            scene->currentId = scene->pendingId;
            scene->pendingId = 0;
            scene->pendingArg = 0;
        }
    }
    return 1;
}
