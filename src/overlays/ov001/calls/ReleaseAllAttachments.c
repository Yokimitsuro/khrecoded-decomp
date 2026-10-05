#include "nitro/types.h"

typedef struct QuadTreeOwner {
    u32 unk_00;
    int **tree;
} QuadTreeOwner;

typedef struct Attachment {
    u8 pad_00[0x24];
    u8 buffer[0x7e];
    u16 nextId;
} Attachment;

typedef struct AttachOwner {
    u8 pad_000[0x284];
    u16 firstAttachmentId;
} AttachOwner;

extern QuadTreeOwner *GetActorRegistry(AttachOwner *owner);
extern Attachment *GetStageLinkedActor(u32 id);
extern void FreeStateBuffer(void *buffer);
extern void QuadTree_RemoveObject(int *tree, Attachment *object);
extern int ReleaseStageSlotEntry(int index, int slot);

void ReleaseAllAttachments(AttachOwner *owner)
{
    QuadTreeOwner *grid = GetActorRegistry(owner);
    u32 id;

    if (grid == NULL) {
        return;
    }
    id = owner->firstAttachmentId;
    if (id == 0) {
        return;
    }
    while (id != 0) {
        Attachment *attachment = GetStageLinkedActor(id);

        if (attachment != NULL) {
            u32 nextId = attachment->nextId;

            FreeStateBuffer(attachment->buffer);
            QuadTree_RemoveObject(*grid->tree, attachment);
            ReleaseStageSlotEntry(7, id);
            id = nextId;
        }
    }
    owner->firstAttachmentId = 0;
}
