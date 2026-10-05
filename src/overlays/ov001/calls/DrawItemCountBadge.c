#include "nitro/types.h"

typedef struct CountPanel {
    u8 pad_000[0x10c];
    u16 shownCount;
    u16 itemCount;
    u32 window;
} CountPanel;

extern void *GetSceneTagTracker(void);
extern int func_ov001_0207123c(void);
extern void func_ov027_020b9d74(int screen, int layer, int x, int y, int width, int height);
extern void func_ov001_02075d1c(CountPanel *panel, u32 window, int row);
extern void *FindActiveRecordById(void *pool, u16 recordId);
extern void func_ov027_020b824c(void *pool, void *record, s16 row, int layer);
extern void DrawGradientRect(u16 x0, u32 y0, u16 x1, u32 y1, u32 mode, u32 color, u32 shade);

void DrawItemCountBadge(CountPanel *panel)
{
    int showBadge = 0;
    void *pool = GetSceneTagTracker();
    int row;
    u16 count;
    int offset;
    int left;

    if (panel->window != 0) {
        func_ov027_020b9d74(func_ov001_0207123c(), 0xb, showBadge, 5, 0xb, 4);
        row = panel->shownCount * 3 - 7;
        if (row >= 1) {
            row = 1;
            showBadge = 1;
        }
        if (panel->itemCount != 0) {
            func_ov001_02075d1c(panel, panel->window, row);
            count = panel->itemCount;
            if (count > 99) {
                count = 99;
            }
            if ((int)count >= 10) {
                func_ov027_020b824c(pool, FindActiveRecordById(pool, count / 10 + 0x78), row + 7, 7);
                func_ov027_020b824c(pool, FindActiveRecordById(pool, count % 10 + 0x46), row + 8, 7);
            } else {
                func_ov027_020b824c(pool, FindActiveRecordById(pool, count + 0x78), row + 7, 7);
            }
            if (showBadge) {
                func_ov027_020b824c(pool, FindActiveRecordById(pool, 0x23), 0, 6);
            }
            panel->shownCount++;
        }
        offset = row * 8 - 6;
        left = 0;
        if (offset > 0) {
            left = offset;
        }
        DrawGradientRect(left, 0x31, offset + 0x43, 0x3f, 0x2000, 0, 0);
    }
}
