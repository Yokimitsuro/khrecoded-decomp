#include "nitro/types.h"

typedef struct {
    int header;
    u32 current : 4;
    u32 target : 4;
} NibblePair;

BOOL HasPendingNibbleChange(NibblePair *pair)
{
    if (pair->current != pair->target) {
        return TRUE;
    }
    return FALSE;
}
