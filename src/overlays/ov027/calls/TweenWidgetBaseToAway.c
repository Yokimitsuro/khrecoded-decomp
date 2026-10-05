#include "nitro/types.h"

typedef struct Widget {
    u8 pad_00[0x24];
    int basePos[2];
    int homePos[2];
    int awayPos[2];
} Widget;

extern void func_ov027_020b9448(void *root, Widget *widget, int duration, const int *from, const int *to, int mode);

void TweenWidgetBaseToAway(void *root, Widget *widget, int duration, int mode)
{
    func_ov027_020b9448(root, widget, duration, widget->basePos, widget->awayPos, mode);
}
