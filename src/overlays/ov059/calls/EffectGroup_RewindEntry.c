#include "nitro/types.h"

extern void *GetGroupMemberData(s32 groupId, s32 entryIndex);
extern int *func_01ffb2f8(void *animObject, int track, int frame);
extern void StopAndClearSoundEmitter(s32 groupId, s32 emitterIndex);

void EffectGroup_RewindEntry(s32 groupId, s32 entryIndex)
{
    void *animObject = GetGroupMemberData(groupId, entryIndex);

    func_01ffb2f8(animObject, 0, 0);
    func_01ffb2f8(animObject, 2, 0);
    StopAndClearSoundEmitter(groupId, 0);
}
