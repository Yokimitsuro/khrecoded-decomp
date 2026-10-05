#include "src/calls/scene_control.h"

void SetPendingScene(s32 sceneId, s32 argument) {
    gSceneController.pendingId = sceneId;
    gSceneController.pendingArg = argument;
}
