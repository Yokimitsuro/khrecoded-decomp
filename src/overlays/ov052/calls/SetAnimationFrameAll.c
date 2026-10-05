#include "nitro/types.h"

extern void *func_01ffb2f8(void *obj, s32 arg1, s32 value);
extern void ApplyModelSetAnimations(void *set, int arg);
extern void TransitionState(void *obj, s32 value);
extern void ResetCueGroupBefore(void *table, int groupId, s32 time);

void SetAnimationFrameAll(int entity, int frame)
{
    int i = 0;
    func_01ffb2f8((void *)(*(int *)(entity + 0x230) + 4), 0, frame);
    for (; i < 2; i++) {
        ApplyModelSetAnimations((void *)(entity + 0xb68 + i * 0x230), frame);
    }
    *(int *)(entity + 0x760) = frame;
    TransitionState((void *)(entity + 0x874), frame);
    ResetCueGroupBefore((void *)(entity + 0xb2c), *(int *)(entity + 0x75c), frame);
}
