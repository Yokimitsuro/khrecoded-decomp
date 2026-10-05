#include "nitro/types.h"

typedef struct {
    u8 pad0[0x9ac];
    u64 flags;
    u8 pad9b4[0xc];
    int action;
} Actor;

BOOL ConsumeActionInterruptFlag(Actor *actor)
{
    BOOL result = FALSE;
    switch (actor->action) {
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1a:
    case 0x1c:
        result = TRUE;
        break;
    case 2:
        if ((actor->flags & 0x1000000000ULL) != 0) {
            result = TRUE;
        }
        actor->flags &= ~0x1000000000ULL;
        break;
    }
    return result;
}
