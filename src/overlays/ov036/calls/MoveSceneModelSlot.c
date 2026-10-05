#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ModelViewer {
    VecFx32 moveFrom;
    VecFx32 moveTo;
    s32 moveMode;
    s32 moveDuration;
    s32 moveTimer;
    u8 pad_024[0x74];
    s32 model;
    u8 pad_09C[0x2c];
    VecFx32 position;
    u8 pad_0D4[0x64];
} ModelViewer;

typedef struct SceneWork {
    u8 pad_0000[0x1094];
    ModelViewer *viewers;
} SceneWork;

typedef struct SceneContext {
    u32 unk_00;
    SceneWork *work;
} SceneContext;

extern SceneContext data_ov036_020c3940;
extern int FindOrAcquireModelSlot(int actorId);
extern void ScreenToTouchVector(ModelViewer *viewer, int x, int y, VecFx32 *out);

void MoveSceneModelSlot(int actorId, int startX, int startY, int endX, int endY, s32 duration)
{
    SceneWork *work = data_ov036_020c3940.work;
    ModelViewer *viewer = &work->viewers[FindOrAcquireModelSlot(actorId)];

    if (viewer->model == 0) {
        return;
    }
    ScreenToTouchVector(viewer, startX, startY, &viewer->moveFrom);
    viewer->position = viewer->moveFrom;
    if (duration == 0) {
        return;
    }
    if (startX == endX && startY == endY) {
        return;
    }
    ScreenToTouchVector(viewer, endX, endY, &viewer->moveTo);
    viewer->moveDuration = duration;
    viewer->moveTimer = duration;
    viewer->moveMode = 3;
}
