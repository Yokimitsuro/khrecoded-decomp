#include "nitro/types.h"

extern void *func_ov027_020b90c4(void *container, int elementId);
extern void func_ov027_020b95a0(void *container, void *element, BOOL visible);

void SetContainerElementVisible_020c9d3c(void *container, int elementId, BOOL visible)
{
    void *element = func_ov027_020b90c4(container, elementId);
    func_ov027_020b95a0(container, element, visible);
}
