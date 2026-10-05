#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xbd38];
    u8 mask[1];
} PanelGrid;

typedef struct {
    s16 x;
    s16 y;
    s16 width;
    s16 height;
} PanelBlocker;

extern PanelGrid *data_ov015_020812e0;
extern s16 data_ov015_0207a1e8[];
extern s16 data_ov015_0207a1f2[];
extern int abs(int value);
extern BOOL IsPointInRect(PanelBlocker *blocker, int tileX, int tileY);

int ClearTilesAlongLine(int x, int y, int targetX, int targetY, PanelBlocker *blockers, int blockerCount, int passCount) {
    int pass;
    int steps;
    int cleared;
    s16 *offsetsX;
    s16 *offsetsY;
    int stepX;
    int stepY;
    int deltaX;
    int deltaY;
    int posX;
    int posY;
    int step;
    int tileX;
    int tileY;
    int blockerIndex;

    deltaX = (x - targetX) << 16;
    deltaY = (y - targetY) << 16;
    cleared = 0;
    if (abs(deltaX) >= abs(deltaY)) {
        steps = abs(deltaX >> 16);
        if (deltaX >= 0) {
            stepX = -0x10000;
        } else {
            stepX = 0x10000;
        }
        stepY = -deltaY / steps;
        offsetsX = data_ov015_0207a1e8;
        offsetsY = data_ov015_0207a1f2;
    } else {
        steps = abs(deltaY >> 16);
        stepX = -deltaX / steps;
        if (deltaY >= 0) {
            stepY = -0x10000;
        } else {
            stepY = 0x10000;
        }
        offsetsX = data_ov015_0207a1f2;
        offsetsY = data_ov015_0207a1e8;
    }
    if (passCount > 5) {
        passCount = 5;
    }
    for (pass = 0; pass < passCount; pass++) {
        posX = (x + offsetsX[pass]) << 16;
        posY = (y - 0x30 + offsetsY[pass]) << 16;
        for (step = 0; step <= steps; step++) {
            tileX = posX >> 16;
            tileY = posY >> 16;
            for (blockerIndex = 0; blockerIndex < blockerCount; blockerIndex++) {
                if (IsPointInRect(&blockers[blockerIndex], tileX, tileY + 0x30)) {
                    break;
                }
            }
            if (blockerIndex < blockerCount) {
                int index = tileY * 0x90 + tileX;
                u8 *mask = data_ov015_020812e0->mask;

                if (mask[index] != 0) {
                    mask[index] = 0;
                    cleared++;
                }
            }
            posX += stepX;
            posY += stepY;
        }
    }
    return cleared;
}
