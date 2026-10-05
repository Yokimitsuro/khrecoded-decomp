#include "nitro/types.h"

typedef struct {
    s16 x;
    s16 y;
} TouchPoint;

typedef struct {
    u8 pad_00[2];
    s8 count;
    u8 pad_03;
    TouchPoint points[4];
} TouchPointList;

void AddTouchPoint(TouchPointList *list, s16 x, s16 y) {
    if (list->count < 4) {
        list->points[list->count].x = x;
        list->points[list->count].y = y;
        list->count++;
    }
}
