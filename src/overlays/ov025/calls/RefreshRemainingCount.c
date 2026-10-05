#include "nitro/types.h"

extern void *data_ov025_020b7780;
extern void func_ov027_020b9e20(void *tiles, int row);
extern void func_ov025_020b584c(void *menu);
extern int CountActiveSlots(void *slots);
extern void DrawRemainingCountText(void *menu, int count);

void RefreshRemainingCount(void) {
    u8 *menu = data_ov025_020b7780;
    func_ov027_020b9e20(menu + 0x64c8, 0x1a);
    func_ov025_020b584c(menu);
    DrawRemainingCountText(menu, CountActiveSlots(menu + 0x64f4));
}
