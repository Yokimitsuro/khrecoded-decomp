#ifndef KH_RECODED_SCENE_CONTROL_H
#define KH_RECODED_SCENE_CONTROL_H

#include "nitro/types.h"

typedef struct SceneEntry {
    s32 overlayId;
    void *classDesc;
} SceneEntry;

typedef struct SceneController {
    void *object;
    SceneEntry *entry;
    s32 currentId;
    s32 pendingId;
    s32 pendingArg;
} SceneController;

extern SceneController gSceneController;
extern SceneEntry gSceneTable[];

#endif
