#include "nitro/types.h"

typedef struct MenuRect {
    u8 pad_00[0x20];
    s16 left;
    s16 top;
    s16 right;
    s16 bottom;
} MenuRect;

typedef struct RectSize {
    int width;
    int height;
} RectSize;

extern MenuRect *data_ov002_0206c46c;

void GetMenuRectSize(RectSize *out)
{
    RectSize size;
    MenuRect *rect = data_ov002_0206c46c;
    size.width = rect->right - rect->left;
    size.height = rect->bottom - rect->top;
    *out = size;
}
