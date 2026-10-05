#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScrollList {
    s8 lastIndex;
    s8 visibleCount;
    s8 pageIndex;
    s8 firstIndex;
    s8 index;
    u8 pad_05[3];
    s32 scroll;
    u8 pad_0c[4];
    s32 pageScroll;
    s32 pageHeight;
} ScrollList;

typedef struct PanelPoint {
    s32 x;
    s32 y;
} PanelPoint;

typedef struct TouchPoint {
    u16 x;
    u16 y;
    u16 touch;
    u16 validity;
} TouchPoint;

typedef struct PanelObject {
    u8 pad_00[0x14];
    s32 slotId;
} PanelObject;

typedef struct PanelState {
    s8 layoutMode;
    u8 pad_01[3];
    s8 rowHeight;
    u8 pad_05[0x98 - 0x5];
    u8 snapped : 1;
    u8 flags98High : 7;
    u8 flags99Low : 4;
    u8 scrolling : 1;
    u8 cancelled : 1;
    u8 flags99High : 2;
    u8 pad_9a[0x258 - 0x9a];
    u8 slotResults[0x2bc - 0x258];
    s32 step;
    s32 touchHeld;
    s32 inputMode;
    u8 pad_2c8[0x2cc - 0x2c8];
    s32 scrollOffset;
    s32 scrollAnchor;
    s32 dragDelta;
    fx32 velocity;
    s32 snapRemainder;
    s32 scrollLimit;
    u8 pad_2e4[0x2ec - 0x2e4];
    ScrollList list;
    u8 pad_304[0x6818 - 0x304];
    u8 panel[1];
} PanelState;

extern PanelState *data_ov013_02074ce0;
extern u16 data_02060500;
extern u16 data_020604fc;

extern BOOL IsButtonBPressed(void);
extern BOOL IsButtonYPressed(void);
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern void func_ov013_020716e4(int mode);
extern u32 UpdateMenuTouch(void);
extern void func_ov013_02070ce8(void);
extern BOOL GetMenuCursorTouch(int index);
extern void GetMenuCursorPosition(PanelPoint *out);
extern BOOL DispatchTouchToWidget(void *root, TouchPoint *point);
extern u16 *func_ov002_02062000(void);
extern u32 ScrollListPad(void *input, ScrollList *list);
extern void LayoutPanelSlotWidgets(void);
extern void func_ov013_0206fbbc(void);
extern void RefreshProgressCaption(void);
extern void func_ov013_02070e40(s32 useAlt);
extern void UpdateWidgetRootOnly(void *root, int keys);
extern void func_ov002_02066ad0(PanelPoint *out);
extern void GetMenuRectSize(PanelPoint *out);
extern void func_ov013_020704a0(void);
extern PanelObject *FindWidgetById(void *panel, int id);
extern void SetEntrySlotsVisible(void *panel, PanelObject *object, BOOL visible);

static inline void ShowPanelArrow(int id, BOOL visible)
{
    u8 *panel = data_ov013_02074ce0->panel;
    SetEntrySlotsVisible(panel, FindWidgetById(panel, id), visible);
}

void UpdatePanelScrollState(void)
{
    PanelState *state;
    s8 prevIndex;
    s8 prevFirst;
    u32 keys;
    u32 result;
    s32 speed;
    s32 limit;
    s32 offset;
    s32 position;
    s32 drag;
    s32 sum;
    s32 step;
    s32 velocity;
    s32 half;
    PanelPoint cursor;
    TouchPoint touch;
    PanelPoint delta;
    PanelPoint size;
    PanelPoint point;
    PanelPoint rect;

    data_ov013_02074ce0->cancelled = 0;
    if (IsButtonBPressed()) {
        PlaySoundEffect(2, 4);
        func_ov013_020716e4(5);
        return;
    }
    if (IsButtonYPressed() && data_ov013_02074ce0->step == 5) {
        if ((data_ov013_02074ce0->list.index + 1) % 10 != 0) {
            func_ov013_020716e4(4);
        }
        return;
    }
    prevIndex = data_ov013_02074ce0->list.index;
    prevFirst = data_ov013_02074ce0->list.firstIndex;
    keys = UpdateMenuTouch();
    if (data_ov013_02074ce0->slotResults[data_ov013_02074ce0->list.index] == 1) {
        data_ov013_02074ce0->slotResults[data_ov013_02074ce0->list.index] = 2;
        func_ov013_02070ce8();
    }
    if (data_ov013_02074ce0->step != 0) {
        if (keys & 8) {
            data_ov013_02074ce0->scrolling = 1;
            data_ov013_02074ce0->step = 10;
        } else if (data_02060500 != 0 || (keys & 1)) {
            data_ov013_02074ce0->touchHeld = 1;
        } else {
            data_ov013_02074ce0->touchHeld = 0;
        }
    }

    switch (data_ov013_02074ce0->step) {
    case 0:
        if (!GetMenuCursorTouch(0)) {
            data_ov013_02074ce0->step = 5;
        }
        break;
    case 5:
        data_ov013_02074ce0->snapped = 0;
        if (keys & 4) {
            GetMenuCursorPosition(&cursor);
            touch.x = cursor.x;
            touch.y = cursor.y;
            data_ov013_02074ce0->inputMode = 3;
            DispatchTouchToWidget(data_ov013_02074ce0->panel, &touch);
            if (data_ov013_02074ce0->cancelled) {
                PlaySoundEffect(2, 4);
                func_ov013_020716e4(5);
            }
        } else {
            result = ScrollListPad(func_ov002_02062000(), &data_ov013_02074ce0->list);
            if (result != 0) {
                if (result & 2) {
                    data_ov013_02074ce0->scrollOffset = -data_ov013_02074ce0->list.scroll;
                    LayoutPanelSlotWidgets();
                }
                func_ov013_0206fbbc();
                RefreshProgressCaption();
                data_ov013_02074ce0->inputMode = 5;
            } else if (!(data_020604fc & 0xc0)) {
                func_ov013_02070e40(0);
                UpdateWidgetRootOnly(data_ov013_02074ce0->panel, *func_ov002_02062000());
                if (data_ov013_02074ce0->layoutMode == 1) {
                    func_ov013_02070e40(1);
                }
            }
        }
        break;
    case 10:
        if (keys & 2) {
            func_ov002_02066ad0(&point);
            delta = point;
            if (delta.y > 3 || delta.y < -3) {
                data_ov013_02074ce0->velocity = delta.y << 12;
            } else {
                data_ov013_02074ce0->velocity = 0;
            }
            data_ov013_02074ce0->scrollOffset += data_ov013_02074ce0->dragDelta;
            data_ov013_02074ce0->dragDelta = 0;
            data_ov013_02074ce0->scrollAnchor = data_ov013_02074ce0->scrollOffset;
            data_ov013_02074ce0->step = 20;
        } else {
            GetMenuRectSize(&rect);
            size = rect;
            data_ov013_02074ce0->dragDelta = size.y;
            sum = data_ov013_02074ce0->scrollOffset + data_ov013_02074ce0->dragDelta;
            if (sum > 0) {
                data_ov013_02074ce0->dragDelta -= sum;
            }
            state = data_ov013_02074ce0;
            drag = state->dragDelta;
            offset = state->scrollOffset;
            sum = offset + drag;
            if (sum < state->scrollLimit) {
                if (offset >= state->scrollLimit) {
                    state->dragDelta = drag + (state->scrollLimit - sum);
                } else if (offset > sum) {
                    state->dragDelta -= drag;
                }
            }
        }
        func_ov013_020704a0();
        break;
    case 20:
        speed = data_ov013_02074ce0->velocity >> 12;
        if (data_ov013_02074ce0->touchHeld != 0) {
            speed = 0;
        }
        if (speed == 0 || (speed < 3 && speed > -3)) {
            state = data_ov013_02074ce0;
            state->snapRemainder = state->scrollOffset % state->rowHeight;
            if (speed == 0) {
                state = data_ov013_02074ce0;
                half = state->rowHeight;
                if (half / 2 > -state->snapRemainder) {
                    if (state->list.pageScroll == 0) {
                        state->snapped = 1;
                    }
                } else {
                    state->snapRemainder += half;
                    state = data_ov013_02074ce0;
                    if (state->list.pageScroll == (state->list.visibleCount - 1) * state->list.pageHeight) {
                        state->snapped = 1;
                    }
                }
            } else if (speed > 0) {
                data_ov013_02074ce0->snapRemainder += data_ov013_02074ce0->rowHeight;
            }
            data_ov013_02074ce0->step = 30;
            break;
        }
        limit = data_ov013_02074ce0->rowHeight / 2 - 1;
        if (speed > limit) {
            speed = limit;
        }
        if (speed < -limit) {
            speed = -limit;
        }
        data_ov013_02074ce0->scrollOffset -= speed;
        velocity = data_ov013_02074ce0->velocity;
        if (velocity > 0) {
            velocity -= 0x800;
        } else {
            velocity += 0x800;
        }
        data_ov013_02074ce0->velocity = velocity;
        state = data_ov013_02074ce0;
        position = state->scrollOffset;
        if (position > 0 && state->velocity < 0) {
            state->scrollOffset = 0;
            data_ov013_02074ce0->velocity = 0;
        } else if (position < state->scrollLimit) {
            if (state->scrollAnchor < state->scrollLimit && position < state->scrollAnchor) {
                state->scrollOffset = state->scrollAnchor;
            } else {
                state->scrollOffset = state->scrollLimit;
            }
            data_ov013_02074ce0->velocity = 0;
        }
        func_ov013_020704a0();
        break;
    case 30:
        velocity = data_ov013_02074ce0->velocity;
        step = data_ov013_02074ce0->snapRemainder;
        if (velocity < 0) {
            if (step < -2) {
                step = -2;
            }
        } else if (velocity > 0) {
            if (step > 2) {
                step = 2;
            }
        } else {
            if (step < -2) {
                step = -2;
            }
            if (step > 2) {
                step = 2;
            }
        }
        data_ov013_02074ce0->snapRemainder -= step;
        data_ov013_02074ce0->scrollOffset -= step;
        func_ov013_020704a0();
        if (data_ov013_02074ce0->snapRemainder == 0) {
            state = data_ov013_02074ce0;
            state->list.pageScroll = state->list.pageIndex * state->list.pageHeight;
            func_ov013_0206fbbc();
            data_ov013_02074ce0->step = 0;
            data_ov013_02074ce0->scrolling = 0;
        }
        break;
    }

    if (data_ov013_02074ce0->list.firstIndex == 0) {
        ShowPanelArrow(2, FALSE);
    } else {
        ShowPanelArrow(2, TRUE);
    }
    if (data_ov013_02074ce0->list.firstIndex >= data_ov013_02074ce0->list.lastIndex - data_ov013_02074ce0->list.visibleCount) {
        ShowPanelArrow(3, FALSE);
    } else {
        ShowPanelArrow(3, TRUE);
    }
    if (prevIndex != data_ov013_02074ce0->list.index ||
        (prevFirst != data_ov013_02074ce0->list.firstIndex && prevIndex != data_ov013_02074ce0->list.index)) {
        PlaySoundEffect(2, 0);
    }
}
