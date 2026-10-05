#include "nitro/types.h"

typedef struct Actor Actor;

extern void Actor_SetModelSetsVisible(Actor *actor, BOOL enable);
extern void func_ov059_020ccd0c(Actor *actor, int mode, BOOL flag);

void Actor_ResetMotion(Actor *actor, int mode, BOOL flag)
{
    if (mode == 2 && flag != FALSE) {
        Actor_SetModelSetsVisible(actor, FALSE);
    }
    func_ov059_020ccd0c(actor, mode, flag);
}
