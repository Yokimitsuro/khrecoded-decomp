#include "libs/nns/snd/sndarc_loader_internal.h"

void SeqDisposeCallback(
    void *memory,
    u32 size,
    u32 data1,
    u32 data2)
{
    NNSSndArc *arc = (NNSSndArc *)data1;
    u32 fileId = data2;

    DisposeCallback(memory, arc, fileId);
    SND_InvalidateSeqData(memory, (u8 *)memory + size);
}
