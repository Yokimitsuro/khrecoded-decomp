#include "nitro/types.h"

u16 *SkipWideString(u16 *text)
{
    while (*text != 0) {
        text++;
    }
    return text + 1;
}
