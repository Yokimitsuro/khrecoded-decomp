#include "nitro/types.h"

int GetTiledPixelIndex(int x, int y, int width, int height) {
    const int blockX = x / 32;
    const int blockY = y / 32;
    const int charX = x % 32;
    const int charY = y % 32;
    const int blocksWide = width / 32;
    const int blocksHigh = height / 32;
    const int blockWidth = (blockX == blocksWide) ? (width % 32) : 32;
    const int blockHeight = (blockY == blocksHigh) ? (height % 32) : 32;

    return width * 32 * blockY + 32 * blockHeight * blockX + blockWidth * charY + charX;
}