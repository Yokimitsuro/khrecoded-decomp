#include "nitro/types.h"

extern void *FindWidgetById(void *container, int elementId);
extern void SetEntrySlotsVisible(void *container, void *element, BOOL visible);

void SetContainerElementVisible(void *container, int elementId, BOOL visible)
{
    SetEntrySlotsVisible(container, FindWidgetById(container, elementId), visible);
}
