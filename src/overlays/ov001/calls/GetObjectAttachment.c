#include "nitro/types.h"

typedef struct StageObject {
    u8 pad_00[0x32];
    u16 attachmentId : 12;
    u16 attachmentFlags : 4;
} StageObject;

extern void *GetStageAttachment(u32 id);

void *GetObjectAttachment(StageObject *object)
{
    if (object == NULL) {
        return NULL;
    }
    if (object->attachmentId == 0) {
        return NULL;
    }
    return GetStageAttachment(object->attachmentId);
}
