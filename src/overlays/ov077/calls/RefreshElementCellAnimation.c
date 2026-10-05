#include "nitro/types.h"

typedef struct ContainerElement {
    u8 pad_00[0x14];
    int spriteIndices[2];
} ContainerElement;

extern ContainerElement *FindWidgetById(void *container, int elementId);
extern void func_0204f218(void *recordArray, int recordIndex, int frames);

void RefreshElementCellAnimation(void *container, int elementId)
{
    ContainerElement *element = FindWidgetById(container, elementId);
    func_0204f218(container, element->spriteIndices[0], 0);
}
