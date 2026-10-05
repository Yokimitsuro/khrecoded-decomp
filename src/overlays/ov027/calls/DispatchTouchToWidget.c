#include "nitro/types.h"

typedef struct TouchPoint {
    u16 x;
    u16 y;
} TouchPoint;

typedef struct Widget {
    u8 pad_00[0xA8];
    void (*onTouch)(struct Widget *widget);
} Widget;

typedef struct WidgetRoot {
    u8 pad_0000[0x6434];
    u8 widgetList[0xC];
} WidgetRoot;

extern Widget *NNS_FndGetNextListObject(void *list, Widget *obj);
extern BOOL HitTestWidget(WidgetRoot *root, int x, int y, Widget *widget);

BOOL DispatchTouchToWidget(WidgetRoot *root, TouchPoint *point)
{
    Widget *widget;
    BOOL handled = FALSE;

    for (widget = NNS_FndGetNextListObject(root->widgetList, NULL); widget != NULL;
         widget = NNS_FndGetNextListObject(root->widgetList, widget)) {
        if (HitTestWidget(root, point->x, point->y, widget)) {
            widget->onTouch(widget);
            handled = TRUE;
            break;
        }
    }
    return handled;
}
