typedef unsigned short u16;

typedef struct ScreenSizeMap {
    u16 width;
    u16 height;
    u16 screenSize;
} ScreenSizeMap;

const ScreenSizeMap *SelectScnSize(const ScreenSizeMap table[4], int width, int height)
{
    int i;

    for (i = 0; i < 4; i++) {
        if (width <= table[i].width && height <= table[i].height) {
            return &table[i];
        }
    }
    return &table[3];
}
