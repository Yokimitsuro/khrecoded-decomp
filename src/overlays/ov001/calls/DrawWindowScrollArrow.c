#include "nitro/types.h"

typedef struct ArrowTiles {
    u16 tiles[4][3][2];
} ArrowTiles;

typedef struct ScrollWindow {
    int kind;
    u8 pad_04[0xc];
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u8 pad_18[0x30];
    int scroll;
} ScrollWindow;

extern const ArrowTiles data_ov001_0209df78;
extern int *data_ov001_020a04e4;

extern int func_ov001_0207123c(void);
extern u16 *func_ov027_020b9e10(int widgets, int layer);
extern void func_ov027_020b9e20(int widgets, int layer);
extern BOOL func_ov001_020645c8(u32 bitOffset);

void DrawWindowScrollArrow(ScrollWindow *window)
{
    int widgets = func_ov001_0207123c();
    u16 *screen = func_ov027_020b9e10(widgets, 0xb);
    ArrowTiles arrows = data_ov001_0209df78;
    int pos;
    int row;
    int dir;
    int kind;
    int right;
    int limit;
    int col;
    int i;
    int j;

    if (func_ov001_020645c8(0x363a)) {
        return;
    }
    pos = (window->scroll + 4) / 8;
    if (*data_ov001_020a04e4 == 8) {
        if (window->kind == 0) {
            row = window->y + window->height - 1;
            if (pos < 0x10) {
                dir = -1;
                kind = 2;
            } else {
                dir = 1;
                kind = 3;
            }
        } else {
            row = window->y - 2;
            if (pos < 0x10) {
                dir = -1;
                kind = 1;
            } else {
                dir = 1;
                kind = 0;
            }
        }
    } else {
        row = window->y + window->height - 1;
        if (pos < 0x10) {
            dir = -1;
            kind = 2;
        } else {
            dir = 1;
            kind = 3;
        }
    }
    pos -= dir * 3;
    right = window->x + window->width - 3;
    limit = right - 2;
    if (pos >= limit) {
        pos = limit;
    }
    if (pos > right) {
        col = right;
    } else if (pos < window->x + 1) {
        col = window->x + 1;
    } else {
        col = pos;
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 2; j++) {
            screen[(row + i) * 32 + col + j] = arrows.tiles[kind][i][j] | 0xe000;
        }
    }
    func_ov027_020b9e20(widgets, 0xb);
}
