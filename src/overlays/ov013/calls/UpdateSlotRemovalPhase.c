#include "nitro/types.h"

typedef struct ObjElement {
    u8 pad_00[0x14];
    s32 animIndex;
} ObjElement;

typedef struct MenuFlags98 {
    u8 scrolling : 1;
    u8 pad1_7 : 7;
} MenuFlags98;

typedef struct MenuState {
    u8 pad_00[2];
    s8 entryCount;
    u8 pad_03;
    s8 scrollStep;
    u8 pad_05[0x98 - 0x5];
    MenuFlags98 flags98;
    u8 pad_99[0x2bc - 0x99];
    s32 phase;
    s32 timer;
    s32 blinkCount;
    u32 blinkMask;
    s32 scrollY;
    u8 pad_2d0[0x2dc - 0x2d0];
    s32 scrollRemaining;
    u8 pad_2e0[0x2ec - 0x2e0];
    s8 slotCount;
    s8 topSlot;
    s8 row;
    s8 visibleRows;
    s8 cursor;
    u8 pad_2f1[0x2fc - 0x2f1];
    s32 rowOffset;
    s32 rowHeight;
    u8 pad_304[0x6818 - 0x304];
    u8 objSub[0x647c];
} MenuState;

extern MenuState *data_ov013_02074ce0;

extern ObjElement *FindWidgetById(void *container, int elementId);
extern void SetEntrySlotsVisible(void *container, ObjElement *element, BOOL visible);
extern s32 func_ov013_02070cb4(void);
extern int DispatchContextCommand(int command, int value, int extra, void *buffer);
extern void ShiftPanelSlotsDown(s32 index);
extern void func_ov013_02070a18(void);
extern void func_ov013_020716e4(char nextState);
extern void ShiftFollowingSlotsUp(void);
extern BOOL LoadPanelSlotCount(void);
extern void EnablePanelWidget(void);
extern void func_ov013_020704a0(void);
extern void func_ov013_0206fbbc(void);
extern void func_ov013_02071444(void);
extern void func_ov013_0206e574(void);

void UpdateSlotRemovalPhase(void)
{
    MenuState *state;
    s32 row = data_ov013_02074ce0->row;
    s32 index;
    s32 digits;
    s32 step;

    switch (data_ov013_02074ce0->phase) {
    case 0:
        data_ov013_02074ce0->timer++;
        if (data_ov013_02074ce0->timer % 2 == 0) {
            digits = data_ov013_02074ce0->cursor + 1;
            index = 0;
            state = data_ov013_02074ce0;
            SetEntrySlotsVisible(data_ov013_02074ce0->objSub, FindWidgetById(state->objSub, row + 0x14),
                                state->blinkCount & 1);
            state = data_ov013_02074ce0;
            SetEntrySlotsVisible(data_ov013_02074ce0->objSub, FindWidgetById(state->objSub, row + 0x1e),
                                state->blinkCount & 1);
            state = data_ov013_02074ce0;
            if (state->blinkMask & 1) {
                SetEntrySlotsVisible(data_ov013_02074ce0->objSub, FindWidgetById(state->objSub, row + 0xc9),
                                    state->blinkCount & 1);
            }
            state = data_ov013_02074ce0;
            if (state->blinkMask & 2) {
                SetEntrySlotsVisible(data_ov013_02074ce0->objSub, FindWidgetById(state->objSub, row + 0x65),
                                    state->blinkCount & 1);
            }
            do {
                state = data_ov013_02074ce0;
                SetEntrySlotsVisible(data_ov013_02074ce0->objSub,
                                    FindWidgetById(state->objSub, index + (row * 3 + 0x2b)),
                                    state->blinkCount & 1);
                index++;
                digits /= 10;
            } while (digits != 0);
            data_ov013_02074ce0->blinkCount++;
            if (data_ov013_02074ce0->blinkCount >= 9) {
                data_ov013_02074ce0->phase = 10;
            }
        }
        break;
    case 10:
        DispatchContextCommand(0x80000002, func_ov013_02070cb4(), 0, 0);
        ShiftPanelSlotsDown(data_ov013_02074ce0->cursor);
        if (data_ov013_02074ce0->cursor < DispatchContextCommand(7, 0, 0, 0)) {
            DispatchContextCommand(0x80000007, DispatchContextCommand(7, 0, 0, 0) - 1, 0, 0);
        }
        data_ov013_02074ce0->entryCount = DispatchContextCommand(1, 0, 0, 0);
        data_ov013_02074ce0->entryCount +=
            (s8)((data_ov013_02074ce0->entryCount + (data_ov013_02074ce0->entryCount + 1) / 10 + 1) / 10);
        data_ov013_02074ce0->slotCount = data_ov013_02074ce0->entryCount;
        if (data_ov013_02074ce0->topSlot > data_ov013_02074ce0->entryCount) {
            data_ov013_02074ce0->topSlot = data_ov013_02074ce0->entryCount;
        }
        func_ov013_02070a18();
        if (data_ov013_02074ce0->slotCount == 0) {
            func_ov013_020716e4(5);
        } else {
            ShiftFollowingSlotsUp();
            data_ov013_02074ce0->phase = 0x14;
        }
        break;
    case 0x14:
        if (LoadPanelSlotCount()) {
            EnablePanelWidget();
            if (data_ov013_02074ce0->slotCount - data_ov013_02074ce0->visibleRows > 0) {
                data_ov013_02074ce0->phase = 0x28;
            } else {
                data_ov013_02074ce0->flags98.scrolling = 1;
                data_ov013_02074ce0->scrollRemaining = -data_ov013_02074ce0->scrollStep;
                data_ov013_02074ce0->phase = 0x1e;
            }
        }
        break;
    case 0x1e:
        step = data_ov013_02074ce0->scrollRemaining;
        if (step < -2) {
            step = -2;
        }
        data_ov013_02074ce0->scrollY -= step;
        data_ov013_02074ce0->scrollRemaining -= step;
        func_ov013_020704a0();
        if (data_ov013_02074ce0->scrollRemaining == 0) {
            data_ov013_02074ce0->flags98.scrolling = 0;
            data_ov013_02074ce0->rowOffset = data_ov013_02074ce0->row * data_ov013_02074ce0->rowHeight;
            func_ov013_0206fbbc();
            data_ov013_02074ce0->phase = 0x28;
        }
        break;
    case 0x28:
        if (data_ov013_02074ce0->cursor >= data_ov013_02074ce0->slotCount) {
            data_ov013_02074ce0->cursor = data_ov013_02074ce0->slotCount - 1;
            data_ov013_02074ce0->row = data_ov013_02074ce0->row - 1;
            data_ov013_02074ce0->rowOffset -= data_ov013_02074ce0->rowHeight;
            func_ov013_0206fbbc();
        }
        data_ov013_02074ce0->phase = 0x32;
        break;
    case 0x32:
        if ((data_ov013_02074ce0->cursor + 1) % 10 != 0) {
            func_ov013_02071444();
        } else {
            func_ov013_0206e574();
        }
        func_ov013_020716e4(1);
        break;
    }
}
