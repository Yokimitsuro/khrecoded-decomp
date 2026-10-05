#include "libs/nns/snd/sndarc_loader_internal.h"

void WaveArcTableDisposeCallback(
    void *memory,
    u32 size,
    u32 data1,
    u32 data2)
{
    SNDWaveArc *waveArc = memory;
    NNSSndArc *arc = (NNSSndArc *)data1;
    u32 fileId = data2;

    (void)size;
    DisposeCallback(memory, arc, fileId);
    SND_DestroyWaveArc(waveArc);
}
