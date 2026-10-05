#include "nitro/types.h"

typedef struct ResourceContainer ResourceContainer;
typedef struct LayoutElement LayoutElement;

extern LayoutElement *func_ov027_020b90c4(ResourceContainer *container, s32 elementId);
extern void func_ov027_020b95a0(ResourceContainer *container, LayoutElement *element, BOOL visible);

void SetLayoutElementVisible(ResourceContainer *layout, s32 elementId, BOOL visible)
{
    func_ov027_020b95a0(layout, func_ov027_020b90c4(layout, elementId), visible);
}
