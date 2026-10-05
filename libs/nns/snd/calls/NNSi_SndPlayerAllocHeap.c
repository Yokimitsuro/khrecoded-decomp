#include "libs/nns/snd/snd_internal.h"

extern void *NNS_FndGetNextListObject(NNSFndList *list, void *object);
extern void NNS_FndRemoveListObject(NNSFndList *list, void *object);
extern void NNS_SndHeapClear(NNSSndHeapHandle heap);

NNSSndHeapHandle NNSi_SndPlayerAllocHeap(int playerNo, NNSSndSeqPlayer *sequencePlayer)
{
    NNSSndPlayer *player = &sSndPlayers[playerNo];
    NNSSndPlayerHeap *heap = (NNSSndPlayerHeap *)NNS_FndGetNextListObject(
        &player->heapList, NULL);

    if (heap == NULL) {
        return NULL;
    }

    NNS_FndRemoveListObject(&player->heapList, heap);
    heap->player = sequencePlayer;
    sequencePlayer->heap = heap;
    NNS_SndHeapClear(heap->handle);
    return heap->handle;
}
