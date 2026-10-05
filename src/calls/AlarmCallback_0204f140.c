#include "libs/nns/snd/strm_internal.h"

extern void DispObjList_Update(NNSSndStrm *stream, NNSSndStrmCallbackStatus status);

void AlarmCallback_0204f140(void *argument)
{
    DispObjList_Update((NNSSndStrm *)argument, NNS_SND_STRM_CALLBACK_INTERVAL);
}
