#include "nitro/types.h"

typedef struct {
    int unk_00;
    int state;
} ObjectStatus;

typedef struct {
    u8 pad_00[0x68];
    ObjectStatus status;
} StatusOwner;

typedef struct {
    StatusOwner *owner;
} StatusHandle;

BOOL IsOwnerStatusActive(StatusHandle *handle)
{
    ObjectStatus *status = &handle->owner->status;

    if (status != NULL && status->state == 1) {
        return TRUE;
    }
    return FALSE;
}
