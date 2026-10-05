#include "nitro/types.h"

typedef struct SlotLink {
    struct SlotLink *next;
    struct SlotLink *prev;
} SlotLink;

extern char *data_0206084c;

/* Unlink from active list, push onto free list */
void FreeSoundHandleSlot(void *entry)
{
    SlotLink *node = (SlotLink *)entry;
    char *base = data_0206084c;

    {
        SlotLink *tail = *(SlotLink **)(base + 0xb471c);
        if (tail == node) {
            *(SlotLink **)(base + 0xb471c) = tail->next;
        }
    }
    if (node->next != NULL) {
        node->next->prev = node->prev;
    }
    if (node->prev != NULL) {
        node->prev->next = node->next;
    }
    node->next = *(SlotLink **)(base + 0xb4718);
    node->prev = NULL;
    if (*(SlotLink **)(base + 0xb4718) != NULL) {
        (*(SlotLink **)(base + 0xb4718))->prev = node;
    }
    *(SlotLink **)(base + 0xb4718) = node;
    *(u16 *)((char *)node + 0x14) = 0;
}
