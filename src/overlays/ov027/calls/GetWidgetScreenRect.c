#include "nitro/types.h"

typedef struct WidgetPoint {
    int x;
    int y;
} WidgetPoint;

typedef struct WidgetRect {
    int x;
    int y;
    int width;
    int height;
} WidgetRect;

typedef struct Widget {
    u8 pad_00[0x1C];
    u16 width;
    u16 height;
    int anchor;
} Widget;

extern void func_ov027_020b9380(void *root, Widget *widget, WidgetPoint *pos, int flags);

WidgetRect *GetWidgetScreenRect(void *root, WidgetRect *rect, Widget *widget)
{
    WidgetPoint pos;

    func_ov027_020b9380(root, widget, &pos, 0);
    rect->x = pos.x >> 12;
    rect->y = pos.y >> 12;
    rect->width = widget->width;
    rect->height = widget->height;
    switch (widget->anchor) {
    case 0:
        rect->x -= rect->width / 2;
        rect->y -= rect->height / 2;
        break;
    case 2:
        rect->x -= rect->width / 2;
        break;
    }
    return rect;
}
