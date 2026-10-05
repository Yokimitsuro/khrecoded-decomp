#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x24];
    u32 flags;
    u8 pad_28[0x30];
    u32 attached;
    void *link;
} OwnerBody;

typedef struct {
    u8 pad_00[0x10];
    OwnerBody body;
} OwnerEntry;

typedef struct {
    u8 pad_00[0x10];
    u8 base[1];
} ChildObject;

typedef struct {
    u32 unk_00;
    ChildObject *object;
    u8 pad_08[0x10];
} ChildSlot;

typedef struct {
    u8 pad_00[0xc];
    OwnerEntry *entry;
    u8 pad_10[0x4c];
    void *buffer;
    u8 pad_60[0x8];
    ChildSlot children[24];
} ChildOwner;

extern void NNSi_FndFreeFromDefaultHeap(void *ptr);
extern void ActorSlot_Unlink(ChildObject *object);
extern void Obj_ShutdownBase(void *base);
extern void func_ov001_0207f234(ChildOwner *owner, void *arg);

void ReleaseChildObjects(ChildOwner *owner, void *arg)
{
    OwnerBody *body = &owner->entry->body;
    int i;

    if (owner->buffer != NULL) {
        if (body->link == NULL) {
            body->flags &= ~1;
        }
        body->attached = 0;
        NNSi_FndFreeFromDefaultHeap(owner->buffer);
        owner->buffer = NULL;
    }
    for (i = 0; i < 24; i++) {
        ChildSlot *slot = &owner->children[i];

        if (slot->object != NULL) {
            ActorSlot_Unlink(slot->object);
            Obj_ShutdownBase(slot->object->base);
            NNSi_FndFreeFromDefaultHeap(slot->object);
            slot->object = NULL;
        }
    }
    func_ov001_0207f234(owner, arg);
}
