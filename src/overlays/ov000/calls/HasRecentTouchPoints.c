#include "nitro/types.h"

typedef struct TouchSample {
    u16 x;
    u16 y;
    u16 touch;
    u16 validity;
} TouchSample;

extern int CopyRecentTouchPoints(TouchSample *table);

BOOL HasRecentTouchPoints(void)
{
    TouchSample points[4];

    return CopyRecentTouchPoints(points) > 0;
}
