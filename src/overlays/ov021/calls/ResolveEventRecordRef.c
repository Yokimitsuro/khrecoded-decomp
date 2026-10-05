#include "nitro/types.h"

typedef struct EventOwner {
    u8 pad0[2];
    u16 baseId;
} EventOwner;

typedef struct StageObject {
    u8 pad0[0x1d0];
    u16 linkType;
    u16 eventId;
} StageObject;

extern void *data_ov021_020b56c4;
extern void *GetStageEventRecord(u32 id);
extern StageObject *FindStageObjectById(u16 id);

void *ResolveEventRecordRef(EventOwner *owner, int ref)
{
    void *record = data_ov021_020b56c4;
    StageObject *object;

    if (record != NULL) {
        switch (ref & 0xff00) {
        case 0:
            record = GetStageEventRecord((u16)(owner->baseId + ref));
            if (record == NULL) {
                return NULL;
            }
            break;
        case 0xf00:
        case 0xff00:
            object = FindStageObjectById(ref);
            if (object == NULL) {
                return NULL;
            }
            if (object->linkType != 1) {
                return NULL;
            }
            return GetStageEventRecord(object->eventId);
        }
    }
    return record;
}
