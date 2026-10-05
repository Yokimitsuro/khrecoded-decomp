#include "libs/nns/snd/sndarc_loader_internal.h"

NNSSndSeqArc *LoadSeqArc(
    u32 fileId,
    NNSSndHeapHandle heap,
    BOOL setAddress)
{
    void *buffer;

    buffer = NNS_SndArcGetFileAddress(fileId);
    if (buffer == NULL) {
        buffer = NNSi_SndArcLoadFile(
            fileId,
            SeqDisposeCallback,
            setAddress ? (u32)NNS_SndArcGetCurrent() : 0,
            fileId,
            heap);

        if (setAddress && buffer != NULL) {
            NNS_SndArcSetFileAddress(fileId, buffer);
        }
    }

    return buffer;
}
