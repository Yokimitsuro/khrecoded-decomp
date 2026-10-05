#include "nitro/types.h"

typedef struct Attachment {
    u8 pad_00[0x30];
    u16 resourceIndex;
    union {
        u16 bits;
        struct {
            u16 nextId : 12;
            u16 isDefault : 1;
            u16 visible : 1;
            u16 reserved : 2;
        };
    };
} Attachment;

typedef struct StageActor {
    u8 pad_000[0x286];
    u16 firstAttachmentId;
} StageActor;

extern char sOv001_Bip_020a0294[];
extern int ReleaseStageSlot(int kind);
extern Attachment *GetStageAttachment(u32 id);
extern void func_01ff88c4(void *dst, u32 value, u32 size);
extern u16 FindActorResourceIndexByName(StageActor *actor, const char *name);
extern int strncmp(const char *a, const char *b, int length);

void AttachActorResource(StageActor *actor, const char *name, int isDefault, int visible)
{
    int id;
    int linkId;
    Attachment *attachment;
    Attachment *link;

    id = ReleaseStageSlot(6);
    if (id == 0) {
        return;
    }
    attachment = GetStageAttachment(id);
    if (attachment == NULL) {
        return;
    }
    func_01ff88c4(attachment, 0, sizeof(Attachment));
    linkId = actor->firstAttachmentId;
    if (linkId == 0) {
        actor->firstAttachmentId = id;
    } else {
        while (linkId != 0) {
            link = GetStageAttachment(linkId);
            if (link == NULL) {
                break;
            }
            linkId = link->nextId;
            if (linkId == 0) {
                link->bits = (link->bits & ~0xfff) | (id & 0xfff);
                break;
            }
        }
    }
    if (attachment == NULL) {
        return;
    }
    attachment->resourceIndex = FindActorResourceIndexByName(actor, name);
    if (isDefault == 0) {
        isDefault = strncmp(name, sOv001_Bip_020a0294, 3) == 0;
    }
    attachment->isDefault = (u16)isDefault;
    attachment->visible = (u16)visible;
}
