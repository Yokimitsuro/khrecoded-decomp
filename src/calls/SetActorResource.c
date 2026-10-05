#include "nitro/types.h"

typedef struct {
    u16 refCount;
    u16 loadedCount;
} SharedRecord;

extern SharedRecord *SND_RegisterSeq(u32 fileId, int kind);
extern void *func_0202c4a0(u32 fileId, int kind);
extern void ApplyRecordTableEntry2(u16 actorIndex, SharedRecord *record, void *data, int kind);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void SetActorResource(int actorIndex, u32 resourceFileId, u32 dataFileId)
{
    void *data = NULL;
    SharedRecord *record = SND_RegisterSeq(resourceFileId, 0xd);

    if (record->loadedCount == 0) {
        data = func_0202c4a0(dataFileId, 0xd);
    }
    ApplyRecordTableEntry2(actorIndex, record, data, 0xd);
    if (data != NULL) {
        NNSi_FndFreeFromDefaultHeap(data);
    }
}
