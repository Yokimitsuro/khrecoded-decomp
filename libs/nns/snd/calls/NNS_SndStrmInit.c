#include "libs/nns/snd/strm_internal.h"

#define offsetof(type, member) ((u32)&(((type *)0)->member))

extern void NNS_FndInitList(NNSFndList *list, u16 offset);
extern void BeginSleep_2(void *argument);
extern void EndSleep(void *argument);

static inline void PM_SetSleepCallbackInfo(
    PMSleepCallbackInfo *info,
    PMSleepCallback callback,
    void *argument)
{
    info->callback = callback;
    info->argument = argument;
}

void NNS_SndStrmInit(NNSSndStrm *stream)
{
    if (!sSndStrmInitialized) {
        NNS_FndInitList(&sSndStrmList, offsetof(NNSSndStrm, link));
        sSndStrmInitialized = TRUE;
    }

    PM_SetSleepCallbackInfo(&stream->preSleepInfo, BeginSleep_2, stream);
    PM_SetSleepCallbackInfo(&stream->postSleepInfo, EndSleep, stream);
    stream->channelMask = 0;
    stream->channelCount = 0;
    stream->activeFlag = FALSE;
    stream->startFlag = FALSE;
}
