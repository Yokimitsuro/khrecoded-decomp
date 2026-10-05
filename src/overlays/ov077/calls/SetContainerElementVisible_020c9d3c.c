#include "nitro/types.h"

extern void *FindWidgetById(void *container, int elementId);
extern void SetEntrySlotsVisible(void *container, void *element, BOOL visible);

void SetContainerElementVisible_020c9d3c(void *container, int elementId, BOOL visible)
{
    void *element = FindWidgetById(container, elementId);
    SetEntrySlotsVisible(container, element, visible);
}
