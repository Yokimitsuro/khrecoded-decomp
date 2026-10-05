#include "nitro/types.h"

extern s8 gScriptState[];
extern int GetCachedSoundParam(void);

u32 IsSoundParamStale(s32 soundId)
{
    s32 cachedParam = GetCachedSoundParam();
    s32 marker = gScriptState[0];

    return !(soundId == marker && (cachedParam == -1 || cachedParam == marker));
}
