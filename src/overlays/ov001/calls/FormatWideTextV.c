#include "nitro/types.h"

typedef char *VaList;

extern int Text_VSNPrintfWide(u16 *dest, u32 destLength, const u16 *format, VaList args);

u16 *FormatWideTextV(const u16 *format, u16 *dest, u32 destLength, VaList args)
{
    Text_VSNPrintfWide(dest, destLength, format, args);
    return dest;
}
