#include "nitro/types.h"

typedef struct Actor Actor;

extern void Actor_SetModelSetsVisible(Actor *actor, BOOL enable);
extern void Actor_ClearMotionState(Actor *actor, int mode, BOOL flag);

void Actor_ResetMotion(Actor *actor, int mode, BOOL flag)
{
    if (mode == 2 && flag != FALSE) {
        Actor_SetModelSetsVisible(actor, FALSE);
    }
    Actor_ClearMotionState(actor, mode, flag);
}
