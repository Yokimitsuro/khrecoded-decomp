#include "nitro/types.h"

u16 *GetTileMapEntry(u16 *tiles, int column, int row) {
    u16 index = (u16)((column / 32) << 10) + (u16)(row << 5);
    index = index + (u16)(column % 32);
    return &tiles[index];
}
