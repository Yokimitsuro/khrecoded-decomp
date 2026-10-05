#include "nitro/types.h"

extern void ReleaseResourceAndDetach(void *object);
extern u32 ReleaseOwnerResource(int parentContext, u32 param2);

void ReleaseChildResourceAndForward(int parentContext, u32 param2) {
    int child = *(int *)(parentContext + 8);
    if (*(int *)(child + 0x84) != 0) {
        *(int *)(child + 0x84) = 0;
        ReleaseResourceAndDetach((void *)(child + 0x88));
    }
    ReleaseOwnerResource(parentContext, param2);
}
