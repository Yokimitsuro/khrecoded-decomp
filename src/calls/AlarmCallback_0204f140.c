#include "libs/nns/snd/strm_internal.h"

extern void func_0204ed48(NNSSndStrm *stream, NNSSndStrmCallbackStatus status);

void AlarmCallback_0204f140(void *argument)
{
    func_0204ed48((NNSSndStrm *)argument, NNS_SND_STRM_CALLBACK_INTERVAL);
}
