#include "nitro/types.h"

typedef struct {
    BOOL (*filter)(s32 recordId, void *userData);
    u8 pad_04[0xC];
    void *userData;
} RecordSearchContext;

BOOL InvokeRecordFilter(s32 recordId, RecordSearchContext *context)
{
    if (context->filter != NULL) {
        return context->filter(recordId, context->userData);
    }
    return TRUE;
}
