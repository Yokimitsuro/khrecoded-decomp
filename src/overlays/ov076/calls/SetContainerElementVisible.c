#include "nitro/types.h"

extern void *func_ov027_020b90c4(void *container, int elementId);
extern void func_ov027_020b95a0(void *container, void *element, BOOL visible);

void SetContainerElementVisible(void *container, int elementId, BOOL visible)
{
    func_ov027_020b95a0(container, func_ov027_020b90c4(container, elementId), visible);
}
