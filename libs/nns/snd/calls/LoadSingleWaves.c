#include "libs/nns/snd/sndarc_loader_internal.h"

BOOL LoadSingleWaves(
    SNDWaveArc *waveArc,
    const SNDBankData *bank,
    int waveArcNo,
    u32 fileId,
    NNSSndHeapHandle heap)
{
    SNDInstPos position = SND_GetFirstInstDataPos(bank);
    SNDInstData instrument;

    if (bank == NULL) {
        return FALSE;
    }

    while (SND_GetNextInstData(bank, &instrument, &position)) {
        if (instrument.type == SND_INST_PCM &&
            waveArcNo == instrument.parameter.wave[1]) {
            if (!SndLoadWaveData(
                waveArc,
                instrument.parameter.wave[0],
                fileId,
                heap)) {
                return FALSE;
            }
        }
    }
    return TRUE;
}
