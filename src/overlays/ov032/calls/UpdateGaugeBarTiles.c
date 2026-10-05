#include "nitro/types.h"

typedef struct {
    const void *source;
    u8 *tiles;
    u8 pad_08[0x18];
    int level;
    int targetLevel;
    BOOL snap;
} GaugeBar;

extern void MIi_CpuCopyFast(const void *src, void *dst, u32 size);
extern void DrawTileColumnPattern(u8 *tiles, u16 x, int pattern);
extern int NNS_GfdRegisterNewVramTransferTask(int command, int offset, void *data, int size);

void UpdateGaugeBarTiles(GaugeBar *bar)
{
    int x;

    if (bar->snap) {
        bar->level = bar->targetLevel;
        bar->snap = FALSE;
    } else {
        int level = bar->level;
        int target = bar->targetLevel;
        if (target < level) {
            level -= 2;
            bar->level = level;
            if (target < level) {
                target = level;
            }
            bar->level = target;
        } else if (target > level) {
            level += 2;
            bar->level = level;
            if (target > level) {
                target = level;
            }
            bar->level = target;
        }
    }
    MIi_CpuCopyFast(bar->source, bar->tiles, 0x160);
    for (x = 0; x < bar->level; x++) {
        DrawTileColumnPattern(bar->tiles, x, 0);
    }
    for (; x < 0x57; x++) {
        DrawTileColumnPattern(bar->tiles, x, 1);
    }
    NNS_GfdRegisterNewVramTransferTask(7, 0x50a0, bar->tiles, 0x160);
}
