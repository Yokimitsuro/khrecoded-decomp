#include "nnsys/snd.h"

int NNS_SndPlayerGetSeqNo(NNSSndHandle *handle)
{
    if (!NNS_SndHandleIsValid(handle)) {
        return -1;
    }
    if (handle->player->seqType != NNS_SND_PLAYER_SEQ_TYPE_SEQ) {
        return -1;
    }

    return handle->player->seqNo;
}
