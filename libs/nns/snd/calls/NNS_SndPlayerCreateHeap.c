#include "libs/nns/snd/snd_internal.h"

extern void *NNS_SndHeapAlloc(
    NNSSndHeapHandle heap,
    u32 size,
    NNSSndHeapDisposeCallback callback,
    u32 data1,
    u32 data2);
extern NNSSndHeapHandle NNS_SndHeapCreate(void *startAddress, u32 size);
extern void NNS_FndAppendListObject(NNSFndList *list, void *object);
extern void PlayerHeapDisposeCallback(void *mem, u32 size, u32 data1, u32 data2);

BOOL NNS_SndPlayerCreateHeap(int playerNo, NNSSndHeapHandle heap, u32 size)
{
    NNSSndHeapHandle playerHeapHandle;
    NNSSndPlayerHeap *playerHeap;
    void *buffer;

    buffer = NNS_SndHeapAlloc(
        heap,
        sizeof(NNSSndPlayerHeap) + size,
        PlayerHeapDisposeCallback,
        0,
        0);
    if (buffer == NULL) {
        return FALSE;
    }

    playerHeap = (NNSSndPlayerHeap *)buffer;
    playerHeap->player = NULL;
    playerHeap->playerNo = playerNo;
    playerHeap->handle = NNS_SND_HEAP_INVALID_HANDLE;

    playerHeapHandle = NNS_SndHeapCreate(
        (u8 *)buffer + sizeof(NNSSndPlayerHeap),
        size);
    if (playerHeapHandle == NNS_SND_HEAP_INVALID_HANDLE) {
        return FALSE;
    }

    playerHeap->handle = playerHeapHandle;
    NNS_FndAppendListObject(&sSndPlayers[playerNo].heapList, playerHeap);
    return TRUE;
}
