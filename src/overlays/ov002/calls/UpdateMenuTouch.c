#include "nitro/types.h"

typedef struct TouchSample {
    u16 x;
    u16 y;
    u16 touch;
    u16 validity;
} TouchSample;

typedef struct TouchPos {
    int x;
    int y;
} TouchPos;

typedef struct MenuPoint {
    s16 x;
    s16 y;
    u8 pad_04[4];
} MenuPoint;

typedef void (*MenuTouchCallback)(int event, TouchPos *pos, int arg);

typedef struct MenuTouch {
    MenuTouchCallback callback;
    u8 wasTouching : 1;
    u8 touching : 1;
    u8 pressed : 1;
    u8 released : 1;
    u8 dragged : 1;
    u8 pad_04_b5 : 3;
    u8 pad_05;
    MenuPoint points[3];
    s16 current;
    s16 startX;
    s16 startY;
    s16 x;
    s16 y;
    s16 prevX;
    s16 prevY;
} MenuTouch;

extern MenuTouch *data_ov002_0206c46c;
extern s8 data_ov002_0206c434[];

extern int CopyRecentTouchPoints(TouchSample *table);
extern void GetMenuRectSize(TouchPos *out);

u32 UpdateMenuTouch(void)
{
    TouchSample samples[4];
    TouchPos pressPos;
    TouchPos releasePos;
    TouchPos delta;
    TouchPos dragPos;
    TouchPos rectSize;
    u8 touching;
    int count;
    int i;
    int x;
    int y;
    u32 events;

    touching = FALSE;
    events = 0;
    count = CopyRecentTouchPoints(samples);
    if (count != 0) {
        for (i = 0; i < count; i++) {
            x = samples[i].x;
            y = samples[i].y;
            if (x >= 256) {
                x = 255;
            } else if (x < 0) {
                x = 0;
            }
            if (y >= 192) {
                y = 191;
            } else if (y < 0) {
                y = 0;
            }
            data_ov002_0206c46c->prevX = data_ov002_0206c46c->x;
            data_ov002_0206c46c->prevY = data_ov002_0206c46c->y;
            data_ov002_0206c46c->x = x;
            data_ov002_0206c46c->y = y;
        }
        touching = TRUE;
    }
    data_ov002_0206c46c->wasTouching = data_ov002_0206c46c->touching;
    data_ov002_0206c46c->touching = touching;
    data_ov002_0206c46c->pressed = (u8)(data_ov002_0206c46c->wasTouching ^ data_ov002_0206c46c->touching) & data_ov002_0206c46c->touching;
    data_ov002_0206c46c->released = ~data_ov002_0206c46c->touching & data_ov002_0206c46c->wasTouching;
    if (data_ov002_0206c46c->pressed) {
        events |= 1;
        data_ov002_0206c46c->prevX = data_ov002_0206c46c->x;
        data_ov002_0206c46c->prevY = data_ov002_0206c46c->y;
        pressPos.x = data_ov002_0206c46c->x;
        pressPos.y = data_ov002_0206c46c->y;
        data_ov002_0206c46c->startX = data_ov002_0206c46c->x;
        data_ov002_0206c46c->startY = data_ov002_0206c46c->y;
        data_ov002_0206c46c->dragged = FALSE;
        for (i = 0; i < 3; i++) {
            data_ov002_0206c46c->points[i].x = pressPos.x;
            data_ov002_0206c46c->points[i].y = pressPos.y;
        }
        if (data_ov002_0206c46c->callback != NULL) {
            data_ov002_0206c46c->callback(1, &pressPos, 0);
        }
    }
    if (data_ov002_0206c46c->released) {
        events |= 2;
        releasePos.x = data_ov002_0206c46c->x;
        releasePos.y = data_ov002_0206c46c->y;
        if (data_ov002_0206c46c->callback != NULL) {
            data_ov002_0206c46c->callback(2, &releasePos, 0);
        }
        if (!data_ov002_0206c46c->dragged) {
            events |= 4;
            if (data_ov002_0206c46c->callback != NULL) {
                data_ov002_0206c46c->callback(4, &releasePos, 0);
            }
        }
    }
    if (data_ov002_0206c46c->touching) {
        GetMenuRectSize(&rectSize);
        delta = rectSize;
        if (delta.x < -4 || delta.x > 4 || delta.y < -4 || delta.y > 4) {
            events |= 8;
            data_ov002_0206c46c->dragged = TRUE;
            dragPos.x = data_ov002_0206c46c->x;
            dragPos.y = data_ov002_0206c46c->y;
            data_ov002_0206c46c->points[data_ov002_0206c46c->current].x = dragPos.x;
            data_ov002_0206c46c->points[data_ov002_0206c46c->current].y = dragPos.y;
            data_ov002_0206c46c->current = data_ov002_0206c434[data_ov002_0206c46c->current];
            if (data_ov002_0206c46c->callback != NULL) {
                data_ov002_0206c46c->callback(8, &dragPos, 0);
            }
        }
    }
    return events;
}
