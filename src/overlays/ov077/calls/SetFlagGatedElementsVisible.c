#include "nitro/types.h"

extern BOOL IsGlobalPackedBitSet(int bitIndex);
extern void SetContainerElementVisible_020c9d3c(void *container, int elementId, BOOL visible);

void SetFlagGatedElementsVisible(void *container, BOOL visible)
{
    if (!IsGlobalPackedBitSet(0xf5b)) {
        visible = FALSE;
    }
    SetContainerElementVisible_020c9d3c(container, 3, visible);
    SetContainerElementVisible_020c9d3c(container, 5, visible);
    SetContainerElementVisible_020c9d3c(container, 4, visible);
}
