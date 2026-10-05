#include "nitro/types.h"

typedef struct WidgetRoot {
    u8 pad_0000[0x6478];
    u32 touchEnabled : 1;
    u32 dpadEnabled : 1;
} WidgetRoot;

void SetWidgetRootTouchEnabled(WidgetRoot *root, BOOL enabled)
{
    root->touchEnabled = (enabled != 0);
}
