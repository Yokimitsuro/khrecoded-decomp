#include "nitro/types.h"

typedef struct ObjSlot {
    u32 inUse;
    u8 resources[0x5c];
    struct ObjSlot *next;
    s16 bit;
} ObjSlot;

typedef struct {
    u8 pad_0000[0x4612];
    u16 bitMask;
    u8 pad_4614[4];
    ObjSlot *head;
    ObjSlot slots[1];
} ObjManager;

extern void func_0204eef4(void *resources);

void ObjManager_FreeSlot(ObjManager *manager, int index)
{
    ObjSlot *slot = &manager->slots[index];
    ObjSlot *cur = manager->head;
    ObjSlot *prev = NULL;

    if (cur == slot) {
        manager->head = slot->next;
    } else {
        while (cur != NULL) {
            if (cur == slot && prev != NULL) {
                prev->next = slot->next;
                break;
            }
            prev = cur;
            cur = cur->next;
        }
    }
    func_0204eef4(slot->resources);
    if (slot->bit != -1) {
        manager->bitMask &= ~(1 << slot->bit);
    }
    slot->inUse = 0;
}
