#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x6c];
    int actionId;
} EventSource;

typedef struct {
    EventSource *source;
    int kind;
} GameEvent;

BOOL IsEventActionAllowed(GameEvent *event)
{
    if (event->kind == 4) {
        switch (event->source->actionId) {
        case 0:
        case 1:
        case 0x17:
        case 0x18:
        case 0x23:
            return FALSE;
        }
    }
    return TRUE;
}
