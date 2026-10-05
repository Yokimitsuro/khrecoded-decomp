#include "nitro/types.h"

typedef struct SceneCtl {
    void *obj;
    void *entry;
    s32   curId;
    s32   pendId;
    s32   pendArg;
} SceneCtl;

extern SceneCtl data_0205fdec;

void SetPendingScene(s32 pendId, s32 pendArg) {
    data_0205fdec.pendId = pendId;
    data_0205fdec.pendArg = pendArg;
}
