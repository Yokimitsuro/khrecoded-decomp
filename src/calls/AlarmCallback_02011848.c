#include "libs/nns/snd/strm_internal.h"

extern void func_02011808(NNSSndStrm *stream, NNSSndStrmCallbackStatus status);

void AlarmCallback_02011848(void *argument)
{
    func_02011808((NNSSndStrm *)argument, NNS_SND_STRM_CALLBACK_INTERVAL);
}
