#include "libs/nns/snd/strm_internal.h"

extern void SND_ClearChannelBit(int alarmNo);
extern void NNS_FndRemoveListObject(NNSFndList *list, void *object);

void ShutdownStrm(NNSSndStrm *stream)
{
    SND_ClearChannelBit(stream->alarmNo);
    NNS_FndRemoveListObject(&sSndStrmList, stream);
    stream->activeFlag = FALSE;
}
