#include "nitro/types.h"

typedef struct NNSFndList {
    void *headObject;
    void *tailObject;
    u16 numObjects;
    u16 offset;
} NNSFndList;

typedef struct ContainerElement {
    u8 pad_00[0x14];
    int objectIndices[2];
} ContainerElement;

typedef struct ResourceContainer {
    u8 objManager[0x6434];
    NNSFndList elementList;
    u8 pad_6440[0x2C];
    ContainerElement *focusedElement;
} ResourceContainer;

extern void func_0204f0d4(ResourceContainer *objManager, int objectIndex);
extern void NNS_FndRemoveListObject(NNSFndList *list, void *object);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void DestroyContainerElement(ResourceContainer *container, ContainerElement *element) {
    int slot;

    if (container->focusedElement == element) {
        container->focusedElement = NULL;
    }
    for (slot = 0; slot < 2; slot++) {
        if (element->objectIndices[slot] != -1) {
            func_0204f0d4(container, element->objectIndices[slot]);
        }
    }
    NNS_FndRemoveListObject(&container->elementList, element);
    if (element != NULL) {
        NNSi_FndFreeFromDefaultHeap(element);
    }
}
