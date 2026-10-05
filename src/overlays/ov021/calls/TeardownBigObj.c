#include "nitro/types.h"

extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void ReleaseResourceAndDetach(u8 *object);

typedef struct {
    u8 pad_000[0x20];
    u32 flags;
    u8 pad_024[0x30];
    u32 field54;
    u32 field58;
    u8 pad_05c[0xa8];
    void *field104;
} BigObj;

void TeardownBigObj(BigObj *obj)
{
    if (obj->field58 == 0) {
        obj->flags = obj->flags & 0xfffffffe;
    }
    obj->field54 = 0;
    NNSi_FndFreeFromDefaultHeap(obj->field104);
    ReleaseResourceAndDetach((u8 *)obj);
}
