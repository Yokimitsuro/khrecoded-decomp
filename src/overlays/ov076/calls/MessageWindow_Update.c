#include "nitro/types.h"
#include "nitro/fx_types.h"

#define REG_DISPCNT (*(volatile u32 *)0x04000000)

typedef struct {
    u8 pad_00[4];
    s16 x;
    s16 y;
    u16 state;
} TouchState;

typedef struct {
    u8 data[0x18];
    u32 unk_0 : 1;
    u32 unk_1 : 1;
    u32 opened : 1;
    u32 unk_3 : 29;
    u8 pad_1c[8];
} FadeAnim;

typedef struct {
    void *func;
    void *context;
} DialogCallback;

typedef struct {
    s16 seqArc;
    s16 index;
} SoundPair;

typedef struct {
    fx32 x;
    fx32 y;
} WidgetPos;

typedef struct {
    int state;
    int mode;
    u16 screen[0x300];
    u8 chars[0x9c0c - 0x608];
    s16 tileX;
    s16 tileY;
    u16 width;
    u16 height;
    FadeAnim fade;
    BOOL active : 1;
    BOOL selectedYes : 1;
    BOOL pressed : 1;
    u8 pad_9c3c[8];
    DialogCallback callbacks[3];
    SoundPair sounds[2];
} Dialog;

extern u16 data_02060500;

extern void SetSecondaryElementEnabled(BOOL enabled);
extern TouchState *func_ov039_020bca20(void);
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern void MessageWindow_BeginClosing(Dialog *dialog);
extern void MessageWindow_UpdateYesNoInput(Dialog *dialog);
extern void SampleTweenValue(FadeAnim *anim, fx32 *value);
extern void func_ov076_020cad10(int x, int y, int width, int height, u16 *screen);
extern void DC_FlushRange(void *buffer, u32 size);
extern void GX_LoadBG1Scr(const void *src, u32 offset, u32 size);
extern void GX_LoadBG1Char(const void *src, u32 offset, u32 size);
extern u16 *G2_GetBG1ScrPtr(void);
extern void NNS_G2dMapScrToCharText(u16 *dst, int width, int height, int x, int y, int stride, int value, int palette);
extern void func_ov076_020cb888(u16 tag, void *info);
extern void *func_ov039_020bc1dc(void);
extern void *FindWidgetById(void *widgets, int id);
extern void func_ov027_020b91e8(void *widgets, void *widget, WidgetPos *pos, int flag);
extern void SetEntrySlotsVisible(void *widgets, void *widget, BOOL visible);
extern void func_ov076_020cae28(Dialog *dialog, int *bottom, int *left, int *right);

void MessageWindow_Update(Dialog *dialog, BOOL handleInput)
{
    fx32 progress;
    WidgetPos markerPos;
    void *cursors[2];
    void *frames[2];
    WidgetPos pos;
    fx32 xs[2];
    int bottom;
    int left;
    int right;
    void *ok;
    void *cursor;
    void (*callback)();
    int width;
    int height;
    int shownWidth;
    int shownHeight;
    u32 size;
    void *widgets;
    void *widget;
    int selected;
    void *other;
    u32 planes;

    if (dialog->active) {
        if (dialog->state == 1) {
            dialog->state = 2;
        } else if (dialog->state == 3) {
            dialog->state = 4;
            SetSecondaryElementEnabled(TRUE);
            planes = (REG_DISPCNT & 0x1f00) >> 8;
            REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | ((planes & ~2) << 8);
            callback = dialog->callbacks[0].func;
            if (callback != NULL) {
                dialog->callbacks[0].func = NULL;
                callback(dialog->callbacks[0].context);
            }
            dialog->sounds[0].seqArc = 0;
            dialog->sounds[0].index = 1;
            dialog->sounds[1].seqArc = 0;
            dialog->sounds[1].index = 3;
        }
        if (handleInput && dialog->state == 2) {
            switch (dialog->mode) {
            case 1:
                if ((data_02060500 & 1) || (data_02060500 & 2) || (data_02060500 & 8)
                    || (func_ov039_020bca20()->state & 3) == 1) {
                    callback = dialog->callbacks[2].func;
                    if (callback != NULL) {
                        callback(dialog->callbacks[2].context, 1);
                    }
                    PlaySoundEffect(0, 1);
                    MessageWindow_BeginClosing(dialog);
                }
                break;
            case 2:
                MessageWindow_UpdateYesNoInput(dialog);
                break;
            }
        }
    }
    if (!dialog->active) {
        if (!dialog->fade.opened) {
            SampleTweenValue(&dialog->fade, &progress);
            width = dialog->width;
            shownWidth = (width * progress + 0x2000) >> 12;
            if (shownWidth > width) {
                shownWidth = width;
            }
            height = dialog->height;
            shownHeight = (height * progress + 0x2000) >> 12;
            if (shownHeight > height) {
                shownHeight = height;
            }
            func_ov076_020cad10(dialog->tileX + (width - shownWidth) / 2, dialog->tileY + (height - shownHeight) / 2, shownWidth, shownHeight, dialog->screen);
            DC_FlushRange(dialog->screen, 0x600);
            GX_LoadBG1Scr(dialog->screen, 0, 0x600);
        } else {
            if (dialog->state == 0) {
                width = dialog->width - 2;
                height = dialog->height - (dialog->mode == 2 ? 4 : 2);
                callback = dialog->callbacks[1].func;
                dialog->callbacks[1].func = func_ov076_020cb888;
                callback(dialog->callbacks[1].context, dialog, width, height);
                if (width != 0 && height != 0) {
                    size = height * (width << 6);
                    DC_FlushRange(dialog->chars, size);
                    GX_LoadBG1Char(dialog->chars, 0x140, size);
                    NNS_G2dMapScrToCharText(G2_GetBG1ScrPtr(), width, height, dialog->tileX + 1, dialog->tileY + 1, 0x20, 5, 0);
                }
                dialog->state = 1;
            }
            dialog->active = TRUE;
        }
    }
    widgets = func_ov039_020bc1dc();
    switch (dialog->mode) {
    case 1:
        widget = FindWidgetById(widgets, 0x27);
        if ((u32)(dialog->state - 1) <= 1) {
            markerPos.x = (dialog->tileX + dialog->width - 2) << 15;
            markerPos.y = ((dialog->tileY + dialog->height) << 15) - 0x1000;
            func_ov027_020b91e8(widgets, widget, &markerPos, 0);
            SetEntrySlotsVisible(widgets, widget, TRUE);
            return;
        }
        SetEntrySlotsVisible(widgets, widget, FALSE);
        return;
    case 2:
        selected = 0;
        ok = FindWidgetById(widgets, 0);
        cursors[0] = FindWidgetById(widgets, 0x23);
        cursors[1] = FindWidgetById(widgets, 0x24);
        frames[0] = FindWidgetById(widgets, 0x25);
        frames[1] = FindWidgetById(widgets, 0x26);
        if ((u32)(dialog->state - 1) <= 1) {
            if (!dialog->selectedYes) {
                selected = 1;
            }
            func_ov076_020cae28(dialog, &bottom, &left, &right);
            pos.x = xs[0] = left << 12;
            pos.y = bottom << 12;
            cursor = cursors[selected];
            func_ov027_020b91e8(widgets, cursor, &pos, 0);
            pos.x = xs[1] = right << 12;
            other = frames[selected == 0];
            func_ov027_020b91e8(widgets, other, &pos, 0);
            pos.x = xs[selected] - 0x2a000;
            func_ov027_020b91e8(widgets, ok, &pos, 0);
            SetEntrySlotsVisible(widgets, ok, TRUE);
            SetEntrySlotsVisible(widgets, cursor, TRUE);
            SetEntrySlotsVisible(widgets, other, TRUE);
            SetEntrySlotsVisible(widgets, cursors[selected == 0], FALSE);
            SetEntrySlotsVisible(widgets, frames[selected], FALSE);
            return;
        }
        if (dialog->state != 4) {
            SetEntrySlotsVisible(widgets, ok, selected);
            SetEntrySlotsVisible(widgets, cursors[0], selected);
            SetEntrySlotsVisible(widgets, cursors[1], selected);
            SetEntrySlotsVisible(widgets, frames[0], selected);
            SetEntrySlotsVisible(widgets, frames[1], selected);
        }
        break;
    }
}

