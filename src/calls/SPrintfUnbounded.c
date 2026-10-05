#include "nitro/types.h"

extern void *Text_VSNPrintfWide(void *dst, u32 len, const char *fmt, void *args);

void *SPrintfUnbounded(void *dst, const char *fmt, ...)
{
    return Text_VSNPrintfWide(dst, 0x7fffffff, fmt, (void *)(((u32)&fmt & ~3u) + 4));
}
