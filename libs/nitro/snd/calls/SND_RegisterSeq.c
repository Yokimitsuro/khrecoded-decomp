extern void *ResCache_FindSlot(int resourceId, int sequenceId);
extern int Heap_GetCurrent(void);
extern int Archive_LoadFile(int resourceId, int sequenceId);
extern void strcpy(void *destination, int source);
extern int gFileLoader[];

typedef struct SNDSequenceSlot {
    unsigned short referenceCount;
    unsigned short state;
    unsigned short flags;
    unsigned short sequenceId;
    int heapId;
    int resource;
    int reserved;
    int nameOrId;
} SNDSequenceSlot;

void *SND_RegisterSeq(int resourceId, int sequenceId)
{
    SNDSequenceSlot *slot = (SNDSequenceSlot *)ResCache_FindSlot(resourceId, sequenceId);
    int heapId;

    if (slot->referenceCount != 0) {
        slot->referenceCount++;
        gFileLoader[5] = 0;
        return slot;
    }

    heapId = gFileLoader[5];
    if (heapId == 0) {
        heapId = Heap_GetCurrent();
    }
    slot->heapId = heapId;
    slot->resource = Archive_LoadFile(resourceId, sequenceId);
    if (resourceId & 0x80000000) {
        slot->nameOrId = resourceId;
    } else {
        strcpy(&slot->nameOrId, resourceId);
    }
    slot->referenceCount = 1;
    slot->state = 0;
    slot->flags = 0;
    slot->sequenceId = (unsigned short)sequenceId;
    return slot;
}