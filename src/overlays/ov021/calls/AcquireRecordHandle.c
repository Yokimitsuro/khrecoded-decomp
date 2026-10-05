#include "nitro/types.h"

typedef struct {
    s32 initialized;
    u8 pad_04[0x28];
} SharedRecordState;

typedef struct {
    SharedRecordState *state;
    int id;
    s32 refCount;
    u8 link[0xc];
} RecordHandle;

typedef struct {
    u8 pad_00[8];
    u32 initArg;
} RecordDesc;

typedef struct {
    u8 pad_00[0x14];
    u8 *context;
    u8 pad_18[0x34];
    u8 handles[0xc];
} RecordOwner;

extern RecordHandle *FindListObjectByIdPrimary(RecordOwner *owner, int id);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void AcquireSharedRecordState(SharedRecordState *obj, s32 key, u32 initArg, u32 context);
extern void NNS_FndAppendListObject(void *list, void *obj);

RecordHandle *AcquireRecordHandle(RecordOwner *owner, RecordDesc *desc, int id, s32 key)
{
    u8 *context = owner->context + 8;
    RecordHandle *handle = FindListObjectByIdPrimary(owner, id);

    if (handle == NULL) {
        handle = NNSi_FndAllocFromDefaultHeap(sizeof(RecordHandle));
        handle->id = id;
        handle->state = NNSi_FndAllocFromDefaultHeap(sizeof(SharedRecordState));
        handle->state->initialized = 0;
        AcquireSharedRecordState(handle->state, key, desc->initArg, (u32)context);
        handle->refCount = 1;
        NNS_FndAppendListObject(owner->handles, handle);
    }
    return handle;
}
