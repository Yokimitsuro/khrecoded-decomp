#include "nitro/types.h"

typedef struct TPCalibrateParam {
    s16 x0;
    s16 y0;
    s16 xDotSize;
    s16 yDotSize;
} TPCalibrateParam;

typedef struct NVRAMConfigTp {
    u16 raw_x1;
    u16 raw_y1;
    u8 dx1;
    u8 dy1;
    u16 raw_x2;
    u16 raw_y2;
    u8 dx2;
    u8 dy2;
} NVRAMConfigTp;

typedef struct NVRAMConfig {
    u8 head[0x58];
    NVRAMConfigTp tp;
} NVRAMConfig;

u32 TP_CalcCalibrateParam(TPCalibrateParam *calibrate, u16 raw_x1, u16 raw_y1, u16 dx1, u16 dy1, u16 raw_x2,
                                   u16 raw_y2, u16 dx2, u16 dy2);

BOOL TP_GetUserInfo(TPCalibrateParam *calibrate)
{
    /* NVRAM user info in the main memory mirror */
    NVRAMConfig *info = (NVRAMConfig *)0x02fffc80;
    u16 x1, y1, x2, y2, dx1, dy1, dx2, dy2;

    x1 = info->tp.raw_x1;
    y1 = info->tp.raw_y1;
    dx1 = (u16)info->tp.dx1;
    dy1 = (u16)info->tp.dy1;
    x2 = info->tp.raw_x2;
    y2 = info->tp.raw_y2;
    dx2 = (u16)info->tp.dx2;
    dy2 = (u16)info->tp.dy2;

    if ((x1 == 0 && x2 == 0 && y1 == 0 && y2 == 0) ||
        TP_CalcCalibrateParam(calibrate, x1, y1, dx1, dy1, x2, y2, dx2, dy2) != 0) {
        calibrate->x0 = 0;
        calibrate->y0 = 0;
        calibrate->xDotSize = 0;
        calibrate->yDotSize = 0;
        return TRUE;
    }
    return TRUE;
}

