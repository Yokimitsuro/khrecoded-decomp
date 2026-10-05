#include "nitro/types.h"

typedef struct {
    u8 data[0xc];
} DigitGlyph;

typedef struct {
    u8 data[8];
} DigitSprite;

typedef struct {
    u8 pad_000[0x28];
    DigitGlyph frameGlyph;
    DigitGlyph digits[10];
    u8 pad_0ac[0x30];
    DigitGlyph slashGlyph;
    DigitSprite frame;
    u8 pad_0f0[0x24];
    DigitSprite currentTens;
    DigitSprite currentOnes;
    DigitSprite slash;
    DigitSprite maximumTens;
    DigitSprite maximumOnes;
    u32 maximum;
    u32 current;
} CounterDisplay;

extern u32 ReadSessionPackedBits(int bitOffset, u32 bitCount);
extern u32 PopCount32(u32 value);
extern void func_ov001_0207ca2c(DigitSprite *sprite, int scale, DigitGlyph *glyph, int color);

void RefreshCounterDigits(CounterDisplay *display)
{
    u32 value;

    display->current = PopCount32(ReadSessionPackedBits(0x3700, 16));
    func_ov001_0207ca2c(&display->frame, 0x1000, &display->frameGlyph, 0x7fff);
    value = display->current;
    func_ov001_0207ca2c(&display->currentOnes, 0x1000, &display->digits[value % 10], 0x7fff);
    func_ov001_0207ca2c(&display->currentTens, 0x1000, &display->digits[value / 10 % 10], 0x7fff);
    func_ov001_0207ca2c(&display->slash, 0x1000, &display->slashGlyph, 0x7fff);
    value = display->maximum;
    func_ov001_0207ca2c(&display->maximumOnes, 0x1000, &display->digits[value % 10], 0x7fff);
    func_ov001_0207ca2c(&display->maximumTens, 0x1000, &display->digits[value / 10 % 10], 0x7fff);
}
