#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s16 left;
    s16 top;
    s16 right;
    s16 bottom;
} Rect16;

typedef struct {
    int handle;
    int x;
    int y;
    u8 pad_0C[8];
    Rect16 bounds;
} SlotItem;

typedef struct {
    int id;
    int rangeStart;
    int rangeEnd;
    u8 pad_0C[0x20];
    int scrollPos;
    u8 pad_30[0x1c];
} ScrollBar;

typedef struct {
    s16 maxX;
    s16 maxY;
    s16 minX;
    s16 minY;
    Rect16 track;
    int grabbed;
    int unk_14;
    int dragDelta;
    int dragStartY;
    int dragCurrentY;
    int dragStartPos;
    int lastY;
    int prevY;
    int flinging;
    int flingTarget;
} DragArea;

typedef struct {
    u8 pad_0000[0x180];
    ScrollBar bars[2];
    u8 pad_0218[0xcbec - 0x218];
    SlotItem trackItems[2];
    u8 pad_cc24[0xf064 - 0xcc24];
    int touchActive;
    int scrollOffsetY;
    u8 pad_f06c[0xf094 - 0xf06c];
    DragArea drag;
} MenuScene;

typedef struct {
    u8 pad_00[4];
    s16 x;
    s16 y;
    u16 state;
} TouchState;

extern MenuScene *data_ov097_020c2540;

extern TouchState *func_ov039_020bca20(void);
extern void EaseScrollTrack(int trackIndex);
extern int GetScrollTrackRow(int trackIndex);
extern BOOL func_ov097_020c1444(int trackIndex);
extern void JumpScrollTrack(int trackIndex, int row);
extern void ResetScrollTrack(int trackIndex);
extern void SetScrollTrackTarget(int trackIndex, int row);
extern void func_ov097_020c08d4(int listIndex, MenuScene *scene);
extern void func_ov097_020bfb58(int listIndex, MenuScene *scene);
extern fx32 FX_Div(fx32 numer, fx32 denom);

static inline fx32 FxMul(fx32 a, fx32 b)
{
    return (fx32)(((fx64)a * b + 0x800LL) >> 12);
}

void UpdateScrollBarDrag_020c0f18(MenuScene *scene)
{
    DragArea *drag = &data_ov097_020c2540->drag;
    TouchState *touch = func_ov039_020bca20();
    ScrollBar *bar = &scene->bars[1];
    SlotItem *lowerItem;
    SlotItem *upperItem;
    int halfHeight;
    int top;
    int bottom;
    int y;
    fx32 ratio;
    int maxPos;

    lowerItem = &scene->trackItems[0];
    upperItem = &scene->trackItems[1];
    drag->track.right = lowerItem->x + lowerItem->bounds.right;
    drag->track.bottom = lowerItem->y + lowerItem->bounds.bottom;
    drag->track.left = lowerItem->x + lowerItem->bounds.left;
    drag->track.top = upperItem->y + upperItem->bounds.top;

    if (((touch->state & 3) == 0 || (touch->state & 3) == 2) && drag->flinging != 0) {
        EaseScrollTrack(1);
        bar->scrollPos = GetScrollTrackRow(1);
        scene->scrollOffsetY = bar->scrollPos * -16;
        func_ov097_020c08d4(1, scene);
        func_ov097_020bfb58(1, scene);
        func_ov097_020c1444(1);
    }

    if ((touch->state & 3) == 0) {
        return;
    }
    if ((touch->state & 3) == 1) {
        if (drag->minX <= touch->x && touch->x <= drag->maxX && drag->minY <= touch->y && touch->y <= drag->maxY) {
            drag->grabbed = 1;
        }
    }
    if ((touch->state & 3) == 2) {
        drag->grabbed = 0;
        drag->unk_14 = 0;
        drag->dragDelta = 0;
        drag->dragStartY = 0;
        drag->dragCurrentY = 0;
        drag->dragStartPos = 0;
        scene->touchActive = 0;
        return;
    }
    if (drag->grabbed != 0) {
        if (touch->state & 1) {
            halfHeight = (drag->track.top - drag->track.bottom) / 2;
            bottom = drag->minY + halfHeight;
            top = drag->maxY - halfHeight;
            scene->touchActive = 1;
            drag->flinging = 0;
            y = touch->y;
            if (y > top) {
                y = top;
            }
            y -= bottom;
            if (y < 0) {
                y = 0;
            }
            ratio = FX_Div(y << 12, (top - bottom) << 12);
            bar->scrollPos = (FxMul((bar->rangeEnd - bar->rangeStart) << 12, ratio) + 0x800) >> 12;
            scene->scrollOffsetY = bar->scrollPos * -16;
            func_ov097_020c08d4(1, scene);
            func_ov097_020bfb58(1, scene);
        }
        return;
    }
    if ((touch->state & 3) == 1) {
        scene->touchActive = 1;
        drag->dragStartY = touch->y;
        drag->dragStartPos = bar->scrollPos;
        drag->lastY = touch->y;
        drag->flinging = 0;
        ResetScrollTrack(1);
    }
    if ((touch->state & 3) == 3) {
        drag->dragCurrentY = touch->y;
        drag->dragDelta = drag->dragCurrentY - drag->dragStartY;
        bar->scrollPos = drag->dragStartPos - drag->dragDelta / 16;
        if (bar->scrollPos < 0) {
            bar->scrollPos = 0;
        }
        maxPos = bar->rangeEnd - bar->rangeStart;
        if (bar->scrollPos > maxPos) {
            bar->scrollPos = maxPos;
        }
        scene->scrollOffsetY = bar->scrollPos * -16;
        func_ov097_020c08d4(1, scene);
        func_ov097_020bfb58(1, scene);
        drag->prevY = drag->lastY;
        drag->lastY = touch->y;
        drag->flingTarget = bar->scrollPos - (drag->lastY - drag->prevY) * 9 / 8;
        drag->flinging = 1;
        if (drag->flingTarget < 0) {
            drag->flingTarget = 0;
        }
        maxPos = bar->rangeEnd - bar->rangeStart;
        if (drag->flingTarget > maxPos) {
            drag->flingTarget = maxPos;
        }
        JumpScrollTrack(1, bar->scrollPos);
        SetScrollTrackTarget(1, drag->flingTarget);
    }
}
