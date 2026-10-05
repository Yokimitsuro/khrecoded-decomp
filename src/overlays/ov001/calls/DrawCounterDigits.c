#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct DigitGraphic {
    u8 data[0xc];
} DigitGraphic;

typedef struct CounterField {
    u8 unk_00;
    u8 bitCount;
    u16 bitOffset;
} CounterField;

typedef struct CounterHud {
    u8 pad_000[0x34];
    DigitGraphic digits[10];
    u8 pad_0AC[0x860];
    CounterField counter;
} CounterHud;

extern u32 ReadSessionPackedBits(int bitOffset, u32 bitCount);
extern void WriteSessionPackedBits(int bitOffset, u32 bitCount, u32 value);
extern void func_ov001_0207ca2c(fx32 *position, fx32 scale, DigitGraphic *digit, int color);

void DrawCounterDigits(CounterHud *hud)
{
    CounterField *counter = &hud->counter;
    u32 value = ReadSessionPackedBits(counter->bitOffset, counter->bitCount);
    fx32 position[2];
    int i;

    if (value > 99) {
        WriteSessionPackedBits(counter->bitOffset, counter->bitCount, 99);
        value = 99;
    }
    position[1] = 0x23000;
    position[0] = 0x1a000;
    for (i = 0; i < 2; i++) {
        func_ov001_0207ca2c(position, 0x1000, &hud->digits[value % 10], 0x7fff);
        value /= 10;
        position[0] -= 0xd000;
    }
}
