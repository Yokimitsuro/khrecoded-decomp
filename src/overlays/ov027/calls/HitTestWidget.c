#include "nitro/types.h"

typedef struct WidgetRect {
    int x;
    int y;
    int width;
    int height;
} WidgetRect;

typedef struct Widget {
    u8 pad_00[0x94];
    u32 disabled : 1;
    u32 focusable : 1;
    u8 pad_98[0x10];
    void (*onTouch)(struct Widget *widget);
} Widget;

extern BOOL IsWidgetMoveFinished(Widget *widget);
extern WidgetRect *GetWidgetScreenRect(void *root, WidgetRect *rect, Widget *widget);

BOOL HitTestWidget(void *root, int x, int y, Widget *widget)
{
    WidgetRect rect;
    BOOL hit = FALSE;

    if (widget->onTouch != NULL && !widget->disabled && widget->focusable &&
        IsWidgetMoveFinished(widget) != FALSE) {
        GetWidgetScreenRect(root, &rect, widget);
        if (rect.width == 0xFFFF || rect.height == 0xFFFF) {
            return FALSE;
        }
        if (rect.x <= x && x <= rect.x + rect.width && rect.y <= y && y <= rect.y + rect.height) {
            hit = TRUE;
        }
    }
    return hit;
}
