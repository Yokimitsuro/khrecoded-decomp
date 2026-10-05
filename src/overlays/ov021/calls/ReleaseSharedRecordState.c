#include "nitro/types.h"

extern void func_0202eb08(void *state);
extern void ReleaseSharedRecordSlot(void *record);

typedef struct {
    u32 initialized;
    void *record;
    u8 state[1];
} SharedRecordState;

void ReleaseSharedRecordState(SharedRecordState *obj)
{
    if (obj->initialized != 0) {
        func_0202eb08(obj->state);
        ReleaseSharedRecordSlot(obj->record);
        obj->initialized = 0;
    }
}
