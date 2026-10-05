#include "nitro/types.h"

extern int AcquireOrRefreshResourceBlock(void *info, int textureId, int flag, void *extra);
extern void BindModelAnimations(void *dst, void *src, int result, u16 field);

BOOL PrepareTextureAndDispatch(void *dst, void *src, void *info, void *extra)
{
    int result = AcquireOrRefreshResourceBlock(info, 0, 1, extra);
    u16 field = *(u16 *)((u8 *)info + 6);
    BindModelAnimations(dst, src, result, field);
    return TRUE;
}
