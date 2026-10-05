#include "nitro/types.h"

typedef struct {
    u32 initialized;
    void *record;
    u8 state[1];
} SharedRecordState;

extern void ReleaseResourceAndDetach(u8 *object);
extern void ReleaseSharedRecordState(SharedRecordState *obj);

// Releases an object and its embedded record state
void ReleaseRecordEntry_020d7600(u8 *object)
{
    ReleaseResourceAndDetach(object);
    ReleaseSharedRecordState((SharedRecordState *)(object + 0x104));
}
