#include "nitro/types.h"

extern u16 FindActorResourceIndexByName(void *actor, const char *name);

void CacheActorNameIndex(u8 *actor, const char *name)
{
    *(u16 *)(actor + 0x33a) = FindActorResourceIndexByName(actor, name);
}
