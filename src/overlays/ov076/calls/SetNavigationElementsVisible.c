#include "nitro/types.h"

extern BOOL IsGlobalPackedBitSet(int bitIndex);
extern void SetContainerElementVisible(void *container, int elementId, BOOL visible);

void SetNavigationElementsVisible(void *container, BOOL visible)
{
    if (!IsGlobalPackedBitSet(0xf5b)) {
        visible = FALSE;
    }
    SetContainerElementVisible(container, 3, visible);
    SetContainerElementVisible(container, 5, visible);
    SetContainerElementVisible(container, 4, visible);
}
