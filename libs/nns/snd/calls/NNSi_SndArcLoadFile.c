#include "libs/nns/snd/sndarc_loader_internal.h"

#define SOUND_HEAP_RESERVED_SIZE 32

void *NNSi_SndArcLoadFile(
    u32 fileId,
    NNSSndHeapDisposeCallback callback,
    u32 data1,
    u32 data2,
    NNSSndHeapHandle heap)
{
    void *buffer;
    u32 length;

    length = NNS_SndArcGetFileSize(fileId);
    if (length == 0) {
        return NULL;
    }
    if (heap == NNS_SND_HEAP_INVALID_HANDLE) {
        return NULL;
    }

    buffer = NNS_SndHeapAlloc(
        heap,
        length + SOUND_HEAP_RESERVED_SIZE,
        callback,
        data1,
        data2);
    if (buffer == NULL) {
        return NULL;
    }

    if (NNS_SndArcReadFile(fileId, buffer, (int)length, 0) != length) {
        return NULL;
    }

    DC_StoreRange(buffer, length);
    return buffer;
}
