#include "nitro/types.h"

typedef struct {
    void *owner;
    void *next;
    void *prev;
} ListNode;

extern void *GetWorldNamedEntry(int id);

/* Looks up a record slot, or the free-actor table. */
void *GetActorRecord(ListNode *self, int index) {
    void *anchor = (u8 *)self + 0x30;
    if (self->next == anchor) {
        goto freeSlot;
    }
    if (self->prev != anchor) {
        goto normal;
    }
freeSlot:
    if (index != 0xff) {
        return GetWorldNamedEntry(index);
    }
    return 0;
normal: {
    u8 *owner = (u8 *)self->owner;
    if (index == 0xff) {
        return 0;
    }
    u8 *base = *(u8 **)(owner + 0xac);
    return base + index * 0x14;
}
}
