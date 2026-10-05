#include "nitro/types.h"

typedef struct Point {
    s32 x;
    s32 y;
} Point;

typedef struct TweenFlags {
    u32 started : 1;
    u32 paused : 1;
    u32 finished : 1;
    u32 reserved : 29;
} TweenFlags;

typedef struct Tween {
    s32 mode;
    s32 duration;
    s32 from;
    s32 to;
    s32 startTick[2];
    TweenFlags flags;
} Tween;

typedef struct Sprite {
    u8 data[0xc];
} Sprite;

typedef struct TimerHud {
    u8 pad_000[4];
    s32 state;
    u8 pad_008[8];
    Sprite icon;
    u8 pad_01c[0x34 - 0x1c];
    Sprite digits[10];
    Sprite colon;
    Sprite signs[2];
    u8 pad_0d0[0xe8 - 0xd0];
    Point iconPos;
    u8 pad_0f0[0x118 - 0xf0];
    u32 frozenTime;
    s32 delta;
    s32 lastDelta;
    s32 colonX;
    s32 minuteX;
    s32 secondX;
    s32 centiX;
    s32 baseX;
    u8 animState;
    s8 lastSecond;
    u8 pad_13a[2];
    s32 paused;
    u8 unk_140_0 : 2;
    u8 frozen : 1;
    u8 countdown : 1;
    u8 hidden : 1;
    u8 muted : 1;
    u8 unk_140_6 : 2;
    u8 pad_141[3];
    Tween tween;
} TimerHud;

extern s32 GetClampedTimerValue(void);
extern void ComputePulseScaleColor(int phase, int *scale, u16 *color);
extern void PlaySoundChecked(void *ptr, int arg);
extern void SampleTweenValue(Tween *tween, s32 *value);
extern void func_02052528(Tween *tween, int mode, int from, int to, int duration);
extern void func_02052570(Tween *tween);
extern void func_ov001_0207ca2c(Point *pos, s32 scale, Sprite *sprite, s32 color);
extern void func_ov001_0207ba1c(int offset, int scale, Sprite *sprite, int color);
extern int FX_Mul(int left, int right);

void UpdateTimerHud(TimerHud *hud)
{
    int scale;
    s32 t;
    s32 speed = 0;
    s32 time = GetClampedTimerValue();
    u16 color;
    Point pos;
    s32 tenths;
    s32 seconds;
    s32 tens;
    s32 minutes;
    s32 hundredths;

    if (hud->state != 2 && hud->paused == 0) {
        if (!hud->countdown && time < 10000) {
            hud->countdown = TRUE;
            if (!hud->frozen) {
                hud->frozenTime = time;
            }
        } else if (hud->countdown && time > 10000) {
            hud->countdown = FALSE;
            hud->lastSecond = 10;
        }
    }

    if (!hud->hidden && (hud->frozen || hud->countdown)) {
        s32 remaining;

        ComputePulseScaleColor((s32)(((s64)(hud->frozenTime - time) << 12) / 1000), &scale, &color);
        if (!hud->muted && hud->paused == 0) {
            remaining = time / 1000;
            if (remaining <= hud->lastSecond) {
                hud->lastSecond = remaining - 1;
                PlaySoundChecked(0, 0x34);
            }
            hud->lastSecond = remaining - 1;
        }
    } else {
        color = 0x7fff;
        if (!hud->hidden && hud->state != 2 && hud->paused == 0 && time < 3000) {
            color = 0x7fff >> 5;
        }
        scale = 0x1000;
    }

    if (hud->delta != 0) {
        if (hud->animState == 0) {
            hud->animState = 1;
            speed = 0x14cd;
        } else if (hud->lastDelta != hud->delta) {
            SampleTweenValue(&hud->tween, &speed);
            speed += 0x100;
            if (speed < 0xc00) {
                speed = 0xc00;
            } else if (speed > 0x14cd) {
                speed = 0x14cd;
            }
            hud->animState = 1;
        }
    }
    hud->lastDelta = hud->delta;

    switch (hud->animState) {
    case 1:
        func_02052528(&hud->tween, 1, speed, 0x400, 1500);
        func_02052570(&hud->tween);
        hud->animState++;
    case 2:
        SampleTweenValue(&hud->tween, &t);
        if (hud->tween.flags.finished) {
            hud->animState = 0;
            hud->delta = 0;
        }
        break;
    }

    func_ov001_0207ca2c(&hud->iconPos, 0x1000, &hud->icon, 0x7fff);
    hundredths = time / 10;
    func_ov001_0207ba1c(hud->centiX, scale, &hud->digits[hundredths % 10], color);
    tenths = hundredths / 10;
    func_ov001_0207ba1c(hud->secondX, scale, &hud->digits[tenths % 10], color);
    seconds = tenths / 10;
    func_ov001_0207ba1c(hud->minuteX, scale, &hud->colon, color);
    func_ov001_0207ba1c(hud->colonX, scale, &hud->digits[seconds % 10], color);
    tens = seconds / 10;
    func_ov001_0207ba1c(-hud->colonX, scale, &hud->digits[tens % 6], color);
    minutes = tens / 6;
    func_ov001_0207ba1c(-hud->minuteX, scale, &hud->colon, color);
    func_ov001_0207ba1c(-hud->secondX, scale, &hud->digits[minutes % 10], color);
    func_ov001_0207ba1c(-hud->centiX, scale, &hud->digits[minutes / 10 % 6], color);

    if (hud->animState != 0) {
        s16 magnitude = (hud->delta < 0) ? -hud->delta : hud->delta;
        s32 step = FX_Mul(0xd000, t);

        pos.y = 0x20000 - FX_Mul(0xd000, 0x1000 - t);
        pos.x = hud->centiX + 0x34800;
        func_ov001_0207ca2c(&pos, t, &hud->digits[0], 0x3ff);
        pos.x -= step;
        func_ov001_0207ca2c(&pos, t, &hud->digits[0], 0x3ff);
        pos.x -= step;
        func_ov001_0207ca2c(&pos, t, &hud->colon, 0x3ff);
        pos.x -= FX_Mul(0x6000, t);
        func_ov001_0207ca2c(&pos, t, &hud->digits[magnitude % 10], 0x3ff);
        magnitude /= 10;
        if (magnitude != 0) {
            pos.x -= step;
            func_ov001_0207ca2c(&pos, t, &hud->digits[magnitude % 10], 0x3ff);
        }
        pos.x -= step - FX_Mul(0x1000, t);
        func_ov001_0207ca2c(&pos, t, &hud->signs[hud->delta > 0], 0x3ff);
    }
}
