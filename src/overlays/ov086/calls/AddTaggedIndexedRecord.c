#include "nitro/types.h"

extern int PXI_Init_0204f0c8(void *base, void *arg, int flags);
extern void IndexedRecord_SetPair(void *base, int index, void *value);
extern void IndexedRecord_ClearActive(void *base, int index);
extern void func_0204f218(void *base, int index, u16 value);

void AddTaggedIndexedRecord(void *base, void *arg, void *value, int tag)
{
    int index = PXI_Init_0204f0c8(base, arg, 0);
    IndexedRecord_SetPair(base, index, value);
    IndexedRecord_ClearActive(base, index);
    func_0204f218(base, index, tag);
}
