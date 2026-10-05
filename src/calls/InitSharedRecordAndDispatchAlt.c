#include "nitro/types.h"

extern void *SND_RegisterSeq(int a, int b);
extern void InitModelInstance(void *dst, void *info, int flags, int one, int b);

void InitSharedRecordAndDispatchAlt(void *dst, int a, void *info, int b)
{
    void *record = SND_RegisterSeq(a, b);
    *(void **)((u8 *)dst + 0x74) = record;
    InitModelInstance(dst, info, 0, 1, b);
}
