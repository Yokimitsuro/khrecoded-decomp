#include "nitro/types.h"

typedef struct ResourceContainer ResourceContainer;

extern BOOL IsGlobalPackedBitSet(int bitIndex);
extern void SetLayoutElementVisible(ResourceContainer *layout, s32 elementId, BOOL visible);

void SetUnlockableElementsVisible(ResourceContainer *layout, BOOL visible)
{
    if (!IsGlobalPackedBitSet(0xf5b)) {
        visible = FALSE;
    }
    SetLayoutElementVisible(layout, 3, visible);
    SetLayoutElementVisible(layout, 5, visible);
    SetLayoutElementVisible(layout, 4, visible);
}
