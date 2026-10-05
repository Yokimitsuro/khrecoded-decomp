#include "nitro/types.h"

typedef void (*ActorCallback)(int entity, int value);

extern int GetTransitionReaction(int entity, int next, int current, int extra);
extern void SelectAnimationById(int selector, int id);
extern int func_0202f4cc(int state, int arg);
extern void SetBlendTableAndBlendTrack(int entity, int blendTable, int trackIndex, int blendIndex, int frameCount);
extern void SelectSlotAnimation(int entity, int index, int state, int frames);

void ChangeActorState(int entity, int blendTable, int state, int blendIndex, int frames)
{
    int i;
    int current = *(int *)(entity + 0x75c);
    int count = frames;
    if (count < 0) {
        count = GetTransitionReaction(entity, state, current, *(int *)(entity + 0x9b8));
    }
    SelectAnimationById(entity + 0x874, state);
    if (count > 0 && *(int *)(entity + 0x768) != 0) {
        int time = func_0202f4cc(*(int *)(entity + 0x230) + 4, 0) - 0x1000;
        ActorCallback callback = *(ActorCallback *)(entity + 0x1fc);
        if (callback != NULL) {
            callback(entity, time);
        }
    }
    SetBlendTableAndBlendTrack(entity, blendTable, 0, blendIndex, count);
    for (i = 0; i < 2; i++) {
        SelectSlotAnimation(entity, i, state, count);
    }
    if (*(ActorCallback *)(entity + 0x1fc) != NULL) {
        (*(ActorCallback *)(entity + 0x1fc))(entity, 0);
    }
    *(int *)(entity + 0x75c) = state;
    *(int *)(entity + 0x768) = 0;
}
