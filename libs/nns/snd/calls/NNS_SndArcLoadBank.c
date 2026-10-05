#include "libs/nns/snd/sndarc_loader_internal.h"

BOOL NNS_SndArcLoadBank(int bankNo, NNSSndHeapHandle heap)
{
    NNSSndArcLoadResult result;

    result = NNSi_SndArcLoadBank(
        bankNo,
        NNS_SND_ARC_LOAD_ALL,
        heap,
        TRUE,
        NULL);

    return result == NNS_SND_ARC_LOAD_SUCCESS ? TRUE : FALSE;
}
