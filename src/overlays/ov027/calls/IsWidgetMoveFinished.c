#include "nitro/types.h"

typedef struct TweenFlags {
    u32 started : 1;
    u32 paused : 1;
    u32 finished : 1;
} TweenFlags;

typedef struct Widget {
    u8 pad_00[0x74];
    TweenFlags tweenXFlags;
    u8 pad_78[0x18];
    TweenFlags tweenYFlags;
} Widget;

BOOL IsWidgetMoveFinished(Widget *widget)
{
    if (widget->tweenXFlags.finished) {
        if (widget->tweenYFlags.finished) {
            return TRUE;
        }
    }
    return FALSE;
}
