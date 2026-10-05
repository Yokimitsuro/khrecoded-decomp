#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ModelViewer {
    VecFx32 moveFrom;
    VecFx32 moveTo;
    s32 moveMode;
    s32 moveRemaining;
    s32 moveDuration;
    u8 pad_024[0xa4];
    VecFx32 position;
    u8 pad_0D4[0x64];
} ModelViewer;

typedef struct SceneWork {
    u8 pad_0000[0xc80];
    s32 skipAnimations;
} SceneWork;

typedef struct SceneContext {
    u32 unk_00;
    SceneWork *work;
} SceneContext;

extern SceneContext data_ov036_020c3940;
extern int EvaluateInterpolationCurve(int mode, unsigned int duration, int remaining);
extern int ScaleAroundPivot(int ratio, int target, int origin);

void StepSceneModelMove(ModelViewer *viewer)
{
    VecFx32 position = viewer->position;
    int remaining = --viewer->moveRemaining;

    if (data_ov036_020c3940.work->skipAnimations != 0 || remaining == 0) {
        position = viewer->moveTo;
        viewer->moveDuration = 0;
    } else {
        int ratio = EvaluateInterpolationCurve(viewer->moveMode, viewer->moveDuration, remaining);

        position.x = ScaleAroundPivot(ratio, viewer->moveTo.x, viewer->moveFrom.x);
        position.y = ScaleAroundPivot(ratio, viewer->moveTo.y, viewer->moveFrom.y);
    }
    viewer->position = position;
}
