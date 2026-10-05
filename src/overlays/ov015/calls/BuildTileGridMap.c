#include "nitro/types.h"

u16 BuildTileGridMap(u16 (*map)[32], u16 tile)
{
    int y;
    int x;

    for (y = 0; y < 24; y++) {
        for (x = 0; x < 32; x++) {
            if (y >= 6 && y < 24 && x >= 0 && x < 18) {
                map[y][x] = tile;
                tile++;
            } else {
                map[y][x] = 0;
            }
        }
    }
    return tile;
}
