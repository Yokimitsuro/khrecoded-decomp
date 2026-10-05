#include "libs/nns/snd/snd_internal.h"

extern void NNS_SndHeapDestroy(NNSSndHeapHandle heap);
extern void NNS_FndRemoveListObject(NNSFndList *list, void *object);

void PlayerHeapDisposeCallback(void *memory, u32, u32, u32)
{
    NNSSndPlayerHeap *heap = (NNSSndPlayerHeap *)memory;
    NNSSndSeqPlayer *sequencePlayer;

    if (heap->handle == NNS_SND_HEAP_INVALID_HANDLE) {
        return;
    }

    NNS_SndHeapDestroy(heap->handle);

    sequencePlayer = heap->player;
    if (sequencePlayer != NULL) {
        sequencePlayer->heap = NULL;
    } else {
        NNS_FndRemoveListObject(&sSndPlayers[heap->playerNo].heapList, heap);
    }
}
