#include "nitro/types.h"

typedef struct {
    u32 initialized;
    void *record;
    u8 state[1];
} SharedRecordState;

extern void ReleaseResourceAndDetach(u8 *object);
extern void func_ov021_020a90a4(SharedRecordState *obj);

// Releases an object and its embedded record state
void ReleaseRecordEntry_020d7600(u8 *object)
{
    ReleaseResourceAndDetach(object);
    func_ov021_020a90a4((SharedRecordState *)(object + 0x104));
}
