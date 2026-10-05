#include "nitro/types.h"

typedef struct GaugeContext {
    u8 pad_00[0x18];
    void *vramTiles;
    void *workTiles;
} GaugeContext;

extern GaugeContext *data_ov001_020a04cc;

extern const u8 data_ov001_0209ddec[];
extern const u8 data_ov001_0209ddf2[];
extern const u8 data_ov001_0209de0e[];
extern const u8 data_ov001_0209de14[];

extern void func_ov001_020738b8(void *tiles, s32 row, const u8 *pattern);
extern void MIi_CpuCopyFast(const void *src, void *dst, u32 size);

void DrawGaugeFill(s32 filledRows)
{
    GaugeContext *gauge = data_ov001_020a04cc;
    s32 row;

    for (row = 0; row < filledRows; row++) {
        func_ov001_020738b8(gauge->workTiles, row, data_ov001_0209ddec);
    }
    func_ov001_020738b8(gauge->workTiles, row++, data_ov001_0209de0e);
    func_ov001_020738b8(gauge->workTiles, row++, data_ov001_0209de14);
    for (; row <= 50; row++) {
        func_ov001_020738b8(gauge->workTiles, row, data_ov001_0209ddf2);
    }
    MIi_CpuCopyFast(gauge->workTiles, gauge->vramTiles, 0xe0);
}
