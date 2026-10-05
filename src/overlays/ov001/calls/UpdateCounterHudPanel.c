#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct DigitGlyph {
    u8 data[0xc];
} DigitGlyph;

typedef struct DigitSprite {
    fx32 x;
    fx32 y;
} DigitSprite;

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
    u32 startTick[2];
    TweenFlags flags;
} Tween;

typedef struct CounterPanel {
    DigitSprite digits[3];
    DigitSprite icon;
    Tween tween;
    u8 shownValue;
    u8 state;
    u8 lastDelta;
} CounterPanel;

typedef struct CounterDisplay {
    u8 pad_000[0x28];
    DigitGlyph frameGlyph;
    DigitGlyph digits[10];
    u8 pad_0ac[0xc];
    DigitGlyph signGlyphs[2];
    DigitGlyph iconGlyph;
    DigitGlyph slashGlyph;
    DigitSprite frame;
    u8 pad_0f0[0x24];
    CounterPanel panel;
} CounterDisplay;

extern u32 ReadSessionPackedBits(int bitOffset, u32 bitCount);
extern void SampleTweenValue(Tween *tween, s32 *output);
extern void func_02052528(Tween *tween, int mode, int from, int to, int duration);
extern void func_02052570(Tween *tween);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern void func_ov001_0207ca2c(DigitSprite *sprite, fx32 scale, DigitGlyph *glyph, u16 color);

void UpdateCounterHudPanel(CounterDisplay *display)
{
    CounterPanel *panel = &display->panel;
    s32 progress;
    s32 target = 0;
    DigitSprite position;
    DigitSprite deltaPosition;
    u32 maximum;
    u32 value;
    int delta;
    u32 shown;
    fx32 offset;
    u32 i;
    u16 color;

    value = ReadSessionPackedBits(0x3700, 16);
    maximum = ReadSessionPackedBits(0x3710, 3) * 20 + 20;
    delta = value - panel->shownValue;

    if (delta != 0) {
        if (panel->state == 0) {
            target = 0x14cd;
            panel->state = 1;
        } else if (panel->lastDelta != delta) {
            SampleTweenValue(&panel->tween, &target);
            target += 0x100;
            if (target < 0xc00) {
                target = 0xc00;
            } else if (target > 0x14cd) {
                target = 0x14cd;
            }
            panel->state = 1;
        }
    }
    panel->lastDelta = delta;

    switch (panel->state) {
    case 1:
        func_02052528(&panel->tween, 1, target, 0x400, 0x5dc);
        func_02052570(&panel->tween);
        panel->state++;
    case 2:
        SampleTweenValue(&panel->tween, &progress);
        if (panel->tween.flags.finished) {
            panel->state = 0;
            panel->shownValue = value;
        }
        break;
    }

    func_ov001_0207ca2c(&display->frame, 0x1000, &display->frameGlyph, 0x7fff);
    shown = panel->shownValue;
    color = shown == maximum ? 0x3ff : 0x7fff;
    for (i = 0; i < 3; i++) {
        func_ov001_0207ca2c(&panel->digits[2 - i], 0x1000, &display->digits[shown % 10], color);
        shown /= 10;
        if (shown == 0) {
            break;
        }
    }
    func_ov001_0207ca2c(&panel->icon, 0x1000, &display->iconGlyph, color);
    position.x = panel->icon.x + 0xd000;
    position.y = panel->icon.y;
    func_ov001_0207ca2c(&position, 0x1000, &display->slashGlyph, 0x7fff);

    if (maximum == 100) {
        offset = 0x41000;
    } else {
        offset = 0x34000;
    }
    for (i = 0; i < 3; i++) {
        position.x = panel->digits[2 - i].x + offset;
        position.y = panel->digits[2 - i].y;
        func_ov001_0207ca2c(&position, 0x1000, &display->digits[maximum % 10], 0x3ff);
        maximum /= 10;
        if (maximum == 0) {
            break;
        }
    }
    position.x = panel->icon.x + offset;
    position.y = panel->icon.y;
    func_ov001_0207ca2c(&position, 0x1000, &display->iconGlyph, 0x3ff);

    if (panel->state != 0) {
        s16 magnitude = delta < 0 ? -delta : delta;
        fx32 step = FX_Mul(0xd000, progress);

        deltaPosition.x = panel->digits[2].x;
        deltaPosition.y = panel->digits[0].y + 0xd000 - FX_Mul(0xd000, 0x1000 - progress);
        for (i = 0; i < 3; i++) {
            func_ov001_0207ca2c(&deltaPosition, progress, &display->digits[magnitude % 10], 0x7fff);
            magnitude /= 10;
            if (magnitude == 0) {
                break;
            }
            deltaPosition.x -= step;
        }
        deltaPosition.x -= step - FX_Mul(0x1000, progress);
        func_ov001_0207ca2c(&deltaPosition, progress, &display->signGlyphs[delta > 0], 0x7fff);
    }
}
