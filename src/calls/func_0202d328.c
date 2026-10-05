#include "nitro/types.h"

extern void RelocateArchiveSections(void *archive, int flags, int extra);

void func_0202d328(void *archive, int extra)
{
    RelocateArchiveSections(archive, 0, extra);
}
