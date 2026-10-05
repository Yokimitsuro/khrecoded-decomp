#include "nitro/types.h"

extern void *NNS_FndAllocFromDefaultExpHeapEx(u32 size, int align);
extern void func_0202edb0(void *object, u16 *counter, int arg, int count);
extern void RebindAnimTracks(void *anim, int blendIndex, int frame);
extern void Flags16_SetBit1(void *object);

void CreateFieldModelObject(void **out, u16 *counter, int arg)
{
    *out = NNS_FndAllocFromDefaultExpHeapEx(0x104, 4);
    func_0202edb0(*out, counter, arg, 4);
    RebindAnimTracks(*out, 0, 0);
    Flags16_SetBit1(*out);
    (*counter)++;
}
