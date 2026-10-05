#include "libs/nns/snd/snd_internal.h"

typedef struct PMSleepCallbackInfo PMSleepCallbackInfo;

extern void SND_Init(void);
extern void BeginSleep(void *arg);
extern void *PXI_Init_0201d30c(void);
extern void PM_PrependPreSleepCallback(PMSleepCallbackInfo *info);
extern void PM_AppendPostSleepCallback(PMSleepCallbackInfo *info);
extern void SndCapture_Reset(void);
extern void NNSi_SndCaptureInit(void);
extern void NNSi_SndPlayerInit(void);

void NNS_SndInit(void)
{
    if (sSndGlobalState.initialized != FALSE) {
        return;
    }

    sSndGlobalState.initialized = TRUE;
    SND_Init();
    sSndGlobalState.preSleepCallback = BeginSleep;
    sSndGlobalState.preSleepArg = NULL;
    sSndGlobalState.postSleepCallback = PXI_Init_0201d30c;
    sSndGlobalState.postSleepArg = NULL;
    PM_PrependPreSleepCallback((PMSleepCallbackInfo *)&sSndGlobalState.preSleepCallback);
    PM_AppendPostSleepCallback((PMSleepCallbackInfo *)&sSndGlobalState.postSleepCallback);
    SndCapture_Reset();
    NNSi_SndCaptureInit();
    NNSi_SndPlayerInit();
    sSndGlobalState.activeState = -1;
    sSndGlobalState.unk4 = 1;
}
