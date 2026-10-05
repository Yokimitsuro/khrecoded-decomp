#include "nitro/types.h"

typedef struct {
    u32 started : 1;
    u32 paused : 1;
    u32 finished : 1;
    u32 reserved : 29;
} TweenFlags;

typedef struct {
    s32 mode;
    s32 durationTicks;
    s32 from;
    s32 to;
    long long startTick;
    TweenFlags flags;
} Tween;

typedef struct {
    s32 layout;
    u8 pad_04[0xd4];
    Tween scrollTween;
    s32 scrollOffset;
} MessageContext;

typedef struct {
    u8 pad_00[0x2e];
    u16 widthTiles;
    u16 heightTiles;
} TextLayer;

typedef struct {
    s32 anchor;
    u8 pad_04[0x14];
    u16 originX;
    u16 originY;
    u8 pad_1c[0x20];
    u16 *text;
    s32 cursorX;
    s32 cursorY;
    u8 pad_48[0x4c];
    TextLayer layer;
} MessageWindow;

extern MessageContext *data_ov001_020a04e4;

extern void DrawTextAnchored(TextLayer *layer, int x, int y, int color, u32 flags, const u16 *text);
extern void DrawSingleLine(TextLayer *layer, int x, int y, int color, int shadowColor, u16 *text, u16 **cursorOut);
extern int func_0200191c(TextLayer *layer, const u16 *text, int flags);
extern int GetNestedModeByte(TextLayer *layer);
extern void Text_UploadTileBuffer(TextLayer *layer);
extern void SampleTweenValue(Tween *tween, s32 *value);
extern void func_ov001_02079524(MessageWindow *window, int left, int top, int right, int bottom);

int UpdateMessageWindowText(MessageWindow *window, BOOL fullRedraw)
{
    MessageContext *context = data_ov001_020a04e4;
    int x;
    int heightPx;
    int widthPx;
    int result = 1;

    if (context->layout == 1) {
        fullRedraw = FALSE;
    }
    if (context->scrollTween.flags.finished || fullRedraw) {
        u16 *text = window->text;
        int color;

        if (text == NULL) {
            context->scrollOffset = 16;
            return 0;
        }
        heightPx = window->layer.heightTiles * 8;
        widthPx = window->layer.widthTiles * 8;
        switch (context->layout) {
        case 1:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 10:
            color = 2;
            break;
        case 2:
        case 8:
        case 9:
            color = 8;
            break;
        }
        if (fullRedraw) {
            u32 flags;

            if (window->anchor == 0 || window->anchor == 2) {
                x = widthPx / 2;
                flags = 0x411;
            } else {
                x = 0;
                flags = 0x209;
            }
            DrawTextAnchored(&window->layer, x + 1, window->cursorY + 1, color - 1, flags, text);
            DrawTextAnchored(&window->layer, x, window->cursorY, color, flags, window->text);
            context->scrollOffset = 16;
            result = 0;
        } else {
            int lineY;
            int lineHeight;

            if (window->anchor == 0 || window->anchor == 2) {
                x = (widthPx + 1) / 2 - (func_0200191c(&window->layer, text, 0) + 1) / 2;
            } else {
                x = 0;
            }
            DrawSingleLine(&window->layer, x + 1, window->cursorY + 1, (color - 1) | 0xb00, color - 1, window->text, NULL);
            DrawSingleLine(&window->layer, x, window->cursorY, color | 0xc00, color, window->text, &window->text);
            lineHeight = GetNestedModeByte(&window->layer);
            lineY = window->cursorY;
            window->cursorX = 0;
            window->cursorY = lineY + (lineHeight + 3);
            if (context->layout == 1) {
                func_ov001_02079524(window, window->originX, window->originY + lineY, window->originX + widthPx, window->originY + heightPx);
            }
        }
        Text_UploadTileBuffer(&window->layer);
    } else {
        s32 value;

        SampleTweenValue(&context->scrollTween, &value);
        context->scrollOffset = value >> 12;
    }
    return result;
}
