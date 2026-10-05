#include "nitro/types.h"

extern void *SND_RegisterSeq(int a, int b);
extern void InitModelInstance(void *dst, int flags, void *info, int one, int b);

void InitSharedRecordAndDispatch(void *dst, int a, void *info, int b)
{
    void *record = SND_RegisterSeq(a, b);
    *(void **)((u8 *)dst + 0x74) = record;
    InitModelInstance(dst, 0, info, 1, b);
}
