#include "nitro/types.h"

struct NNSFndList {
    void *head_object;
    void *tail_object;
    u16 num_objects;
    u16 offset;
};

extern void *NNS_FndGetNextListObject(void *list, void *obj);
extern void StepWidgetMoveTween(void *owner, void *element);

struct Owner {
    u8 pad_0000[0x6434];
    struct NNSFndList elementList;
};

void ForEachListElement(struct Owner *owner) {
    void *element;

    for (element = NNS_FndGetNextListObject(&owner->elementList, 0);
         element != 0;
         element = NNS_FndGetNextListObject(&owner->elementList, element)) {
        StepWidgetMoveTween(owner, element);
    }
}
