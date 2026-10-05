#include "nitro/types.h"

typedef struct Widget {
    u8 pad_00[0x2C];
    int homePos[2];
} Widget;

extern void StartWidgetMoveTween(void *root, Widget *widget, int duration, const int *from, const int *to, int mode);

void TweenWidgetToHome(void *root, Widget *widget, int duration, int mode)
{
    StartWidgetMoveTween(root, widget, duration, NULL, widget->homePos, mode);
}
