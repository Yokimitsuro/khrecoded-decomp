#include "libs/nns/snd/strm_internal.h"

extern void StrmCallback(NNSSndStrm *stream, NNSSndStrmCallbackStatus status);

void AlarmCallback(void *argument)
{
    StrmCallback((NNSSndStrm *)argument, NNS_SND_STRM_CALLBACK_INTERVAL);
}
