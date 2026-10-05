#include "nitro/types.h"

extern void func_ov001_02090258(void *block);
extern BOOL func_ov001_02090268(void *actor);

BOOL HandleActorLifecycleEvent(int event, void *actor)
{
    switch (event) {
    case 0:
        func_ov001_02090258(actor);
        break;
    case 1:
        func_ov001_02090268(actor);
        break;
    }
    return TRUE;
}
