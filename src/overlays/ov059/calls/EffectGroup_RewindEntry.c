#include "nitro/types.h"

extern void *func_ov021_020a8f0c(s32 groupId, s32 entryIndex);
extern int *func_01ffb2f8(void *animObject, int track, int frame);
extern void func_ov021_020a8e34(s32 groupId, s32 emitterIndex);

void EffectGroup_RewindEntry(s32 groupId, s32 entryIndex)
{
    void *animObject = func_ov021_020a8f0c(groupId, entryIndex);

    func_01ffb2f8(animObject, 0, 0);
    func_01ffb2f8(animObject, 2, 0);
    func_ov021_020a8e34(groupId, 0);
}
