#include "nitro/types.h"

typedef struct ResourceContainer ResourceContainer;

extern ResourceContainer *func_ov039_020bc1ec(void);
extern void *FindWidgetById(ResourceContainer *container, int id);
extern void SetEntrySlotsVisible(ResourceContainer *container, void *element, BOOL visible);

void SetStatusElementVisible(int elementId, BOOL visible)
{
    ResourceContainer *container = func_ov039_020bc1ec();

    SetEntrySlotsVisible(container, FindWidgetById(container, elementId), visible);
}
