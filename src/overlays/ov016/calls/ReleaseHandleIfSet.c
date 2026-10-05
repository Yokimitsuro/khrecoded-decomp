#include "nitro/types.h"

extern void ReleaseResourceAndDetach(void);
extern void NNSi_FndFreeFromDefaultHeap(s32 handle);

void ReleaseHandleIfSet(s32 *handle)
{
    if (*handle != 0) {
        ReleaseResourceAndDetach();
        NNSi_FndFreeFromDefaultHeap(*handle);
        *handle = 0;
    }
}
