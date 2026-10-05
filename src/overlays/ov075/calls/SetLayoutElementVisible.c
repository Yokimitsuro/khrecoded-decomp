#include "nitro/types.h"

typedef struct ResourceContainer ResourceContainer;
typedef struct LayoutElement LayoutElement;

extern LayoutElement *FindWidgetById(ResourceContainer *container, s32 elementId);
extern void SetEntrySlotsVisible(ResourceContainer *container, LayoutElement *element, BOOL visible);

void SetLayoutElementVisible(ResourceContainer *layout, s32 elementId, BOOL visible)
{
    SetEntrySlotsVisible(layout, FindWidgetById(layout, elementId), visible);
}
