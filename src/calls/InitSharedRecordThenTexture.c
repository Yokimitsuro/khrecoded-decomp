#include "nitro/types.h"

extern void *SND_RegisterSeq(int a, int b);
extern int AcquireOrRefreshResourceBlock(void *info, int flags, int one);
extern void BindModelAnimations(void *dst, void *src, int result, int b);

BOOL InitSharedRecordThenTexture(void *dst, void *src, int a, int b)
{
    void *record = SND_RegisterSeq(a, b);
    *(void **)((u8 *)dst + 0xc) = record;
    int result = AcquireOrRefreshResourceBlock(record, 0, 1);
    BindModelAnimations(dst, src, result, b);
    return TRUE;
}
