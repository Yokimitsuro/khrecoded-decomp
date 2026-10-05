#include "nitro/types.h"

typedef struct TouchSample {
    u16 x;
    u16 y;
    u16 touch;
    u16 validity;
} TouchSample;

extern int TP_GetLatestIndexInAuto(void);
extern void TP_GetCalibratedPoint(TouchSample *out, TouchSample *raw);
extern void MI_CpuCopy8(const void *src, void *dst, u32 len);
extern TouchSample data_02060534[];

int CopyRecentTouchPoints(TouchSample *table)
{
    int latest;
    int i;
    s16 count = 0;

    if (!((*(volatile u16 *)0x02ffffa8 & 0x8000) >> 15)) {
        TouchSample point;

        latest = TP_GetLatestIndexInAuto();
        i = 0;
        latest -= 3;

        for (; i < 4; i++) {
            int index = latest + i;
            TouchSample *sample;

            if (index < 0) {
                index += 5;
            }
            sample = &data_02060534[index];
            if (sample->touch != 0 && sample->validity == 0) {
                TP_GetCalibratedPoint(&point, sample);
                if (point.x <= 0xff && point.y <= 0xbf) {
                    MI_CpuCopy8(&point, &table[count++], 8);
                }
            }
        }
    }

    return count;
}
