#include "nitro/types.h"

typedef struct TextWindow {
    u8 pad[0x2e];
    u16 widthTiles;
    u16 heightTiles;
} TextWindow;

extern int GetNestedModeByte(TextWindow *window);
extern void func_0200177c(TextWindow *window, int x, int y, int color, int altColor, int colorHigh, u16 *text, BOOL shadow);

void DrawCenteredWindowText(TextWindow *window, u16 *text) {
    u16 *cursor = text;
    int width = window->widthTiles * 8;
    int height = window->heightTiles * 8;
    int lineHeight = GetNestedModeByte(window) + 1;
    int textHeight = lineHeight;

    while (*cursor != 0) {
        if (*cursor == '\n') {
            textHeight += lineHeight;
        }
        cursor++;
    }
    func_0200177c(window, (width + 1) / 2, (height + 1) / 2 - (textHeight + 1) / 2, 2, 10, 10, text, FALSE);
}
