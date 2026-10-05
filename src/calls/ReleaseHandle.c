#include "nitro/types.h"

typedef struct Handle {
    void *target;
    u8 active;
} Handle;

extern void DetachHandle(Handle *handle);

void ReleaseHandle(Handle *handle)
{
    if (handle->active && handle->target != NULL) {
        DetachHandle(handle);
    }
    handle->active = 0;
    handle->target = NULL;
}
