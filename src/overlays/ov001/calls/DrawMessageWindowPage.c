#include "nitro/types.h"

typedef struct ModeContext {
    s32 mode;
    u8 pad_04[0xd4];
    u8 tween[0x18];
    u32 unused0 : 2;
    u32 instant : 1;
    u32 unused3 : 29;
    s32 fadeLevel;
} ModeContext;

typedef struct MessageWindow {
    u8 pad_00[0x18];
    u16 x;
    u16 y;
    u8 pad_1c[0x1c];
    const u16 *text;
    const u16 *cursor;
    u8 pad_40[0x54];
    u8 textLayer[0x2e];
    u16 widthTiles;
    u16 heightTiles;
} MessageWindow;

extern ModeContext *data_ov001_020a04e4;
extern void DrawTextAnchored(void *layer, int x, int y, int color, u32 flags, const u16 *text);
extern void DrawTextPackedColor(void *layer, int x, int y, int color, int colorLow, int colorHigh, const u16 *text);
extern void DrawCenteredWindowText(void *layer, const u16 *text);
extern void Text_UploadTileBuffer(void *layer);
extern void SampleTweenValue(void *tween, s32 *value);
extern void StartWindow1Fade(MessageWindow *window, int left, int top, int right, int bottom);

int DrawMessageWindowPage(MessageWindow *window, int force)
{
    ModeContext *context = data_ov001_020a04e4;
    s32 value;

    if (context->instant || force != 0) {
        int width;
        int height;

        if (*window->cursor == 0) {
            context->fadeLevel = 0x10;
            return 0;
        }
        switch (context->mode) {
        case 3:
            DrawCenteredWindowText(window->textLayer, window->text);
            break;
        case 1:
            DrawTextAnchored(window->textLayer, 1, 1, 1, 0, window->text);
            DrawTextAnchored(window->textLayer, 0, 0, 2, 0, window->text);
            break;
        case 4:
        case 5:
        case 6:
        case 7:
        case 10:
            DrawTextPackedColor(window->textLayer, 0, 0, 2, 0xe, 0xc, window->text);
            break;
        case 2:
        case 8:
        case 9:
            DrawTextAnchored(window->textLayer, 1, 1, 7, 0, window->text);
            DrawTextAnchored(window->textLayer, 0, 0, 8, 0, window->text);
            break;
        }
        Text_UploadTileBuffer(window->textLayer);
        while (*window->cursor != 0) {
            window->cursor++;
        }
        width = window->widthTiles * 8;
        height = window->heightTiles * 8;
        if (context->mode == 1) {
            StartWindow1Fade(window, window->x, window->y, window->x + width, window->y + height);
        }
    } else {
        SampleTweenValue(context->tween, &value);
        context->fadeLevel = value >> 12;
    }
    return 1;
}
