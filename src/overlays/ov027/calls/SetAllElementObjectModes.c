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
extern void func_ov027_020b97d8(ResourceContainer *container, void *element, int mode);

void SetAllElementObjectModes(ResourceContainer *container, int mode) {
    void *element;

    element = NNS_FndGetNextListObject(&container->elementList, NULL);
    while (element != NULL) {
        func_ov027_020b97d8(container, element, mode);
        element = NNS_FndGetNextListObject(&container->elementList, element);
    }
}
