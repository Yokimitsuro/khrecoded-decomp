#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    s32 pending;
} Request;

BOOL Request_IsIdle(void *owner, Request *request)
{
    switch (request->pending) {
    case 0:
        break;
    default:
        return FALSE;
    }
    return TRUE;
}
