#include "nitro/types.h"

typedef struct {
    s16 x;
    s16 y;
} PanelPoint;

typedef struct {
    s16 x;
    s16 y;
    s16 width;
    s16 height;
} PanelBlocker;

typedef struct {
    s16 active;
    u8 pad_02[0x16];
} PanelSlot;

typedef struct {
    u8 pad_00[0x20];
    PanelPoint start;
    PanelPoint points[5];
    s16 pointCount;
    u8 pad_3a[0x1b];
    s8 slotCount;
    u8 pad_56[0x2e];
    PanelSlot slots[1];
} PanelTrace;

extern PanelTrace *data_ov015_020812e0;
extern PanelPoint *gWirelessModeDataTables[];
extern int ClearTilesAlongLine(int x, int y, int targetX, int targetY, PanelBlocker *blockers, int blockerCount, int passCount);

int ClearTracedPathTiles(void)
{
    PanelBlocker blockers[9];
    int cleared;
    int pointCount;
    int blockerCount;
    int i;
    int slotCount;
    PanelPoint *slotPoints;
    PanelTrace *trace;

    cleared = 0;
    trace = data_ov015_020812e0;
    slotCount = trace->slotCount;
    blockerCount = cleared;
    slotPoints = gWirelessModeDataTables[slotCount];
    for (i = 0; i < slotCount; i++) {
        if (trace->slots[i].active == 1) {
            blockers[blockerCount].x = slotPoints[i].x;
            blockers[blockerCount].y = slotPoints[i].y;
            blockers[blockerCount].width = 0x28;
            blockers[blockerCount].height = 0x28;
            blockerCount++;
        }
    }
    if (blockerCount <= 0) {
        return 0;
    }
    {
        pointCount = trace->pointCount;

        if (pointCount != 0) {
            int prevX = data_ov015_020812e0->start.x;
            int prevY = data_ov015_020812e0->start.y;

            for (i = 0; i < pointCount; i++) {
                int curX = data_ov015_020812e0->points[i].x;
                int curY = data_ov015_020812e0->points[i].y;

                if (prevX < 0 || prevY < 0) {
                    prevX = curX;
                    prevY = curY;
                }
                cleared += ClearTilesAlongLine(prevX, prevY, curX, curY, blockers, blockerCount, 5);
                prevX = curX;
                prevY = curY;
            }
        }
    }
    return cleared;
}
