#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x48];
    void *field48;
} OverlayObject;

extern void ReleaseResourceAndDetach();
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);

void ReleaseField48(OverlayObject *obj)
{
    if (obj->field48 != 0) {
        ReleaseResourceAndDetach();
        NNSi_FndFreeFromDefaultHeap(obj->field48);
        obj->field48 = 0;
    }
}
