#include "nnsys/snd.h"

void NNS_SndPlayerSetSeqArcNo(NNSSndHandle *handle, int sequenceArchiveNo, int index)
{
    if (!NNS_SndHandleIsValid(handle)) {
        return;
    }

    handle->player->seqType = NNS_SND_PLAYER_SEQ_TYPE_SEQARC;
    handle->player->seqNo = (u16)sequenceArchiveNo;
    handle->player->seqArcIndex = (u16)index;
}
