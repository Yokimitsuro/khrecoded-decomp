#include "nitro/types.h"

typedef struct NNSFndList {
    void *headObject;
    void *tailObject;
    u16 numObjects;
    u16 offset;
} NNSFndList;

typedef struct ResourceContainer {
    u8 objManager[0x6434];
    NNSFndList elementList;
} ResourceContainer;

extern void *NNS_FndGetNextListObject(NNSFndList *list, void *object);
extern void DestroyContainerElement(ResourceContainer *container, void *element);

void DestroyAllContainerElements(ResourceContainer *container) {
    void *element;
    void *next;

    element = NNS_FndGetNextListObject(&container->elementList, NULL);
    while (element != NULL) {
        next = NNS_FndGetNextListObject(&container->elementList, element);
        DestroyContainerElement(container, element);
        element = next;
    }
}
