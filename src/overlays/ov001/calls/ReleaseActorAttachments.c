#include "nitro/types.h"

typedef struct {
    u8 pad[0x32];
    u16 nextId : 12;
    u16 kind : 4;
} Attachment;

typedef struct {
    u8 pad[0x286];
    u16 firstAttachmentId;
} Actor;

extern Attachment *GetStageAttachment(u32 id);
extern int ReleaseStageSlotEntry(int index, int slot);

void ReleaseActorAttachments(Actor *actor) {
    u16 id = actor->firstAttachmentId;
    if (id != 0) {
        while (id != 0) {
            Attachment *attachment = GetStageAttachment(id);
            if (attachment != NULL) {
                u16 next = attachment->nextId;
                ReleaseStageSlotEntry(6, id);
                id = next;
            }
        }
        actor->firstAttachmentId = 0;
    }
}
