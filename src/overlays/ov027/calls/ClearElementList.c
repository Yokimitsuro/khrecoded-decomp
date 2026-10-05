#include "nitro/types.h"

struct NNSFndList {
    void *head_object;
    void *tail_object;
    u16 num_objects;
    u16 offset;
};

extern void *NNS_FndGetNextListObject(void *list, void *obj);
extern void NNS_FndRemoveListObject(struct NNSFndList *list, void *object);

struct ListElement {
    u8 pad_00[0x20];
    u32 flags;
};

void ClearElementList(struct NNSFndList *list) {
    struct ListElement *element;
    struct ListElement *next;

    element = (struct ListElement *)NNS_FndGetNextListObject(list, 0);
    while (element != 0) {
        next = (struct ListElement *)NNS_FndGetNextListObject(list, element);
        element->flags = (element->flags & 0xfffffffe) | 1;
        NNS_FndRemoveListObject(list, element);
        element = next;
    }
    *(u32 *)((u8 *)list + 0x18) = 0;
}
