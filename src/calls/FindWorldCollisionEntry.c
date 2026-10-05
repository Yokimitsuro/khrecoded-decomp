#include "nitro/types.h"

typedef struct CollisionWorld CollisionWorld;

extern char *CollModel_FindEntry(CollisionWorld *world, void *name);
extern CollisionWorld *gActorRegistry;

char *FindWorldCollisionEntry(void *name)
{
    return CollModel_FindEntry(gActorRegistry, name);
}
