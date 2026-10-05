#include "nitro/types.h"

extern void *SND_RegisterSeq(s32 key, s32 context);
extern void DispatchResourceLoad(void *state, u32 initArg, s32 recordArg, u32 context);

typedef struct {
    u32 initialized;
    void *record;
    u8 state[1];
} SharedRecordState;

void AcquireSharedRecordState(SharedRecordState *obj, s32 key, u32 initArg, u32 context)
{
    if (obj->initialized == 0) {
        void *record = SND_RegisterSeq(key, context);
        obj->record = record;
        DispatchResourceLoad(obj->state, initArg, *(s32 *)((u8 *)record + 0xc), context);
        obj->initialized = 1;
    }
}
