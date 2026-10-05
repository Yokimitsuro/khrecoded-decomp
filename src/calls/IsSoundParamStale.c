#include "nitro/types.h"

extern s8 data_02055e00[];
extern int GetCachedSoundParam(void);

u32 IsSoundParamStale(s32 soundId)
{
    s32 cachedParam = GetCachedSoundParam();
    s32 marker = data_02055e00[0];

    return !(soundId == marker && (cachedParam == -1 || cachedParam == marker));
}
