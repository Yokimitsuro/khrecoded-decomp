#include "nitro/types.h"

typedef struct QueryObject {
    u8 pad_00[4];
    s32 kind;
} QueryObject;

BOOL QueryFilter_IsKind24(void *context, QueryObject *object)
{
    if (object != NULL && object->kind == 24) {
        return TRUE;
    }
    return FALSE;
}
