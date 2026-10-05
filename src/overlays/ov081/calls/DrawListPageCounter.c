#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x820];
    u8 counterChars[4];
} Ov081State;

typedef struct {
    u8 kind;
} EntryList;

extern const char data_ov081_020c5d60[];
extern const char data_ov081_020c5d70[];
extern void func_ov081_020c5480(Ov081State *state, EntryList *list, int *total, int *before);
extern void *SPrintfUnbounded(void *dst, const char *fmt, ...);
extern void func_ov081_020c5550(void *charBase, int bg, const void *text, int x, int y, int areaWidth, int areaHeight, int tile);

void DrawListPageCounter(Ov081State *state, EntryList *list)
{
    int total;
    int before;
    char text[12];

    if (list->kind == 1) {
        func_ov081_020c5480(state, list, &total, &before);
        SPrintfUnbounded(text, data_ov081_020c5d60, before + 1, total);
    } else {
        SPrintfUnbounded(text, data_ov081_020c5d70);
    }
    func_ov081_020c5550(state->counterChars, 1, text, 0x1a, 1, 4, 2, 0x44);
}
