#include "nitro/types.h"

extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void ReleaseResourceAndDetach(void *object);

void DestroyDisplayObject(int owner) {
    int object;

    object = *(int *)(owner + 0x3a4);
    if (object != 0) {
        if (*(int *)(object + 0x58) == 0) {
            *(u32 *)(object + 0x20) = *(u32 *)(object + 0x20) & 0xfffffffe;
        }
        *(u32 *)(object + 0x54) = 0;
        NNSi_FndFreeFromDefaultHeap(*(void **)(object + 0x104));
        ReleaseResourceAndDetach((void *)object);
        NNSi_FndFreeFromDefaultHeap((void *)object);
        *(u32 *)(owner + 0x3a4) = 0;
    }
}
