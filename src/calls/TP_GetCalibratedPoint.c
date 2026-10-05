#include "nitro/types.h"

typedef struct {
    u16 x;
    u16 y;
    u16 touch;
    u16 validity;
} TouchSample;

typedef struct {
    u8 pad_00[0x34];
    u16 calibrated;
} TouchState;

typedef struct {
    s32 offsetX;
    s32 pad_04;
    s32 scaleX;
    s32 offsetY;
    s32 pad_10;
    s32 scaleY;
} TouchCalibration;

extern TouchState data_02059784;
extern TouchCalibration data_020597a0;
extern s64 _ll_mul(s64 a, s64 b);

void TP_GetCalibratedPoint(TouchSample *out, const TouchSample *in)
{
    if (data_02059784.calibrated == 0) {
        out->x = in->x;
        out->y = in->y;
        out->touch = in->touch;
        out->validity = in->validity;
        return;
    }
    {
        TouchCalibration *calib = &data_020597a0;

        out->touch = in->touch;
        out->validity = in->validity;
        if (in->touch == 0) {
            out->x = 0;
            out->y = 0;
            return;
        }
        {
            int rawX = in->x << 2;
            s64 diffX = (s64)rawX - calib->offsetX;

            out->x = (u16)(s32)(_ll_mul(calib->scaleX, diffX) >> 22);
            if ((s16)out->x < 0) {
                out->x = 0;
            } else if ((s16)out->x > 0xff) {
                out->x = 0xff;
            }
        }
        {
            int rawY = in->y << 2;
            s64 diffY = (s64)rawY - calib->offsetY;

            out->y = (u16)(s32)(_ll_mul(calib->scaleY, diffY) >> 22);
            if ((s16)out->y < 0) {
                out->y = 0;
                return;
            }
            if ((s16)out->y > 0xbf) {
                out->y = 0xbf;
            }
        }
    }
}
