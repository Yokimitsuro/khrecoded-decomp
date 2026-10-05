#include "nitro/types.h"

typedef struct PoolEntry {
    u32 words[3];
} PoolEntry;

extern PoolEntry *GetPool3Entry(void *owner, int index);

void CopyPool3Entry(PoolEntry *dest, void *owner, int index)
{
    *dest = *GetPool3Entry(owner, index);
}
