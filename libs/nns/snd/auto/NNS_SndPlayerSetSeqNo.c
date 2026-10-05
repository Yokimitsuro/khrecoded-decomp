#include "nnsys/snd.h"

void NNS_SndPlayerSetSeqNo(NNSSndHandle *handle, int sequenceNo)
{
    if (!NNS_SndHandleIsValid(handle)) {
        return;
    }

    handle->player->seqType = NNS_SND_PLAYER_SEQ_TYPE_SEQ;
    handle->player->seqNo = (u16)sequenceNo;
}
