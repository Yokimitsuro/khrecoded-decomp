#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x10];
    u8 *shadeRamp;
} GaugeSetup;

extern GaugeSetup data_ov001_0209ee14;

void DrawGaugeSpan(u8 *tiles, int firstCell, int markCell, int cellCount, int rowCount, int barWidth,
                           int leftInset, int topRow)
{
    int padded;
    int extra;
    int total;
    int from;
    int limit;
    int i;
    int x;
    int row;
    u8 shade;
    u8 *p;

    extra = 0;
    total = leftInset + barWidth;
    padded = (total + 7) / 8 * 8;
    if (total % 8 == 0) {
        extra = 8;
    }
    from = 7 - cellCount;
    limit = extra + (padded - (markCell + leftInset + 1));
    for (i = 0; i < cellCount; i++) {
        x = extra + (padded - (leftInset + (firstCell + i) + 1));
        shade = data_ov001_0209ee14.shadeRamp[from + i];
        if (x <= limit && shade == 0xf) {
            shade = 8;
        }
        if (x < 0) {
            x = 0;
        }
        p = tiles + ((x % 8) / 2 + ((x / 8) * 32 + topRow * 4));
        if ((x & 1) != 0) {
            for (row = 0; row < rowCount; row++) {
                *p = (u8)((*p & 0xf) | (shade << 4));
                p += 4;
            }
        } else {
            for (row = 0; row < rowCount; row++) {
                *p = (u8)((*p & 0xf0) | shade);
                p += 4;
            }
        }
    }
}
