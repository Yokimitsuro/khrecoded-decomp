#include "libs/nns/snd/sndarc_loader_internal.h"

#define SOUND_HEAP_RESERVED_SIZE 32

extern void SingleWaveDisposeCallback(
    void *memory,
    u32 size,
    u32 data1,
    u32 data2);

BOOL SndLoadWaveData(
    SNDWaveArc *waveArc,
    int waveNo,
    u32 fileId,
    NNSSndHeapHandle heap)
{
    SNDWaveData *buffer;
    u32 length;
    u32 begin;
    u32 end;
    u32 waveCount;

    if (SND_GetWaveDataAddress(waveArc, waveNo) != NULL) {
        return TRUE;
    }
    waveCount = SND_GetWaveDataCount(waveArc);

    begin = waveArc->waveOffset[waveArc->waveCount + waveNo];
    if (waveNo < waveCount - 1) {
        end = waveArc->waveOffset[waveArc->waveCount + waveNo + 1];
    } else {
        end = waveArc->fileHeader.fileSize;
    }
    length = end - begin;

    if (heap == NNS_SND_HEAP_INVALID_HANDLE) {
        return FALSE;
    }
    buffer = NNS_SndHeapAlloc(
        heap,
        length + SOUND_HEAP_RESERVED_SIZE,
        SingleWaveDisposeCallback,
        (u32)waveArc,
        (u32)waveNo);
    if (buffer == NULL) {
        return FALSE;
    }
    if (NNS_SndArcReadFile(fileId, buffer, (int)length, (int)begin) != length) {
        return FALSE;
    }

    DC_StoreRange(buffer, length);
    SND_SetWaveDataAddress(waveArc, waveNo, buffer);
    return TRUE;
}
