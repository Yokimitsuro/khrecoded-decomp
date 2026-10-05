#include "nitro/types.h"

typedef struct ViewerAnimation {
    u8 bindingState[0x74];
    s32 model;
    u8 pad_78[0x60];
    s16 trackCounts[5];
    u8 pad_e2[0x2a];
} ViewerAnimation;

typedef struct ModelViewer {
    u8 pad_000[0x24];
    ViewerAnimation anim;
    s32 blendIndex;
    u8 pad_134[0x4];
} ModelViewer;

typedef struct SceneWork {
    u8 pad_0000[0xc80];
    s32 skipAnimations;
    u8 pad_0C84[0x410];
    ModelViewer *viewers;
} SceneWork;

typedef struct SceneContext {
    u32 unk_00;
    SceneWork *work;
} SceneContext;

extern SceneContext data_ov036_020c3940;
extern int FindOrAcquireModelSlot(int actorId);
extern void selectJointAnimationBlend(void *animationState, u16 trackIndex, void *blendTable, s16 blendIndex);

void SetSceneModelBlendIndex(int actorId, int blendIndex)
{
    SceneWork *work = data_ov036_020c3940.work;
    ModelViewer *viewer = &work->viewers[FindOrAcquireModelSlot(actorId)];
    ViewerAnimation *anim = &viewer->anim;
    int track;

    if (viewer->anim.model == 0) {
        return;
    }
    viewer->blendIndex = blendIndex;
    if (work->skipAnimations != 0 && viewer->blendIndex == 0 && viewer->anim.trackCounts[0] > 1) {
        viewer->blendIndex = 1;
    }
    for (track = 0; track < 5; track++) {
        if (blendIndex < anim->trackCounts[track]) {
            selectJointAnimationBlend(anim, track, anim->trackCounts, blendIndex);
        }
    }
}
