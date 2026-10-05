#include "nitro/types.h"

typedef struct CollisionWorld CollisionWorld;

extern char *CollModel_FindEntry(CollisionWorld *world, void *name);
extern CollisionWorld *data_0206083c;

char *FindWorldCollisionEntry(void *name)
{
    return CollModel_FindEntry(data_0206083c, name);
}
