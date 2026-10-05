#include "libs/nns/snd/sndarc_loader_internal.h"

#define SOUND_HEAP_RESERVED_SIZE 32

SNDWaveArc *NNS_SndArcLoadWaveArcTable(
    u32 fileId,
    NNSSndHeapHandle heap,
    BOOL setAddress)
{
    u32 fileSize;
    SNDWaveArc *waveArc;
    u32 waveCount;
    u32 tableSize;
    int result;

    waveArc = NNS_SndArcGetFileAddress(fileId);
    if (waveArc == NULL) {
        if (NNS_SndArcReadFile(
            fileId,
            sWaveArcHeaderBuffer,
            0x3c,
            0) != 0x3c) {
            return NULL;
        }
        waveCount = sWaveArcHeader.waveCount;
        tableSize = waveCount * sizeof(u32);
        fileSize = tableSize * 2;
        if (heap == NNS_SND_HEAP_INVALID_HANDLE) {
            return NULL;
        }
        waveArc = NNS_SndHeapAlloc(
            heap,
            fileSize + 0x5c,
            WaveArcTableDisposeCallback,
            setAddress ? (u32)NNS_SndArcGetCurrent() : 0,
            fileId);
        if (waveArc == NULL) {
            return NULL;
        }
        result = NNS_SndArcReadFile(
            fileId,
            waveArc,
            (int)(tableSize + 0x3c),
            0);
        if (result != tableSize + 0x3c) {
            return NULL;
        }
        MI_CpuCopy8(
            waveArc->waveOffset,
            &waveArc->waveOffset[waveArc->waveCount],
            tableSize);
        MI_CpuFill8(waveArc->waveOffset, 0, tableSize);
        DC_StoreRange(waveArc, fileSize + 0x3c);
        if (setAddress) {
            NNS_SndArcSetFileAddress(fileId, waveArc);
        }
    }
    return waveArc;
}
