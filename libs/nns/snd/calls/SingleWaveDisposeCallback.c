#include "libs/nns/snd/sndarc_loader_internal.h"

void SingleWaveDisposeCallback(
    void *memory,
    u32 size,
    u32 data1,
    u32 data2)
{
    SNDWaveArc *waveArc = (SNDWaveArc *)data1;
    u32 waveNo = data2;

    if (memory == SND_GetWaveDataAddress(waveArc, (int)waveNo)) {
        SND_SetWaveDataAddress(waveArc, (int)waveNo, NULL);
    }
    SND_InvalidateWaveData(memory, (u8 *)memory + size);
}
