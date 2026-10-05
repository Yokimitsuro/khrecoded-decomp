#include "libs/nns/snd/strm_internal.h"

extern void WMi_StartParentEx(NNSSndStrm *stream, NNSSndStrmCallbackStatus status);

void AlarmCallback_02011848(void *argument)
{
    WMi_StartParentEx((NNSSndStrm *)argument, NNS_SND_STRM_CALLBACK_INTERVAL);
}
