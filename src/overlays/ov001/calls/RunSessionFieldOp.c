#include "nitro/types.h"

typedef struct SessionFieldOp {
    u8 pad[0xc];
    u16 bitOffset;
    u16 bitCount;
    s16 op;
    u16 operand;
} SessionFieldOp;

extern u32 ReadSessionPackedBits(int bitOffset, u32 bitCount);
extern void WriteSessionPackedBits(int bitOffset, u32 bitCount, u32 value);
extern u32 _u32_div_f(u32 numerator, u32 denominator);

BOOL RunSessionFieldOp(SessionFieldOp *item) {
    u32 value;
    u16 result;

    result = 0;
    value = ReadSessionPackedBits(item->bitOffset, item->bitCount);
    switch (item->op) {
    case 0:
    case 2:
        break;
    case 7:
        result = item->operand;
        break;
    case 3:
        result = value + item->operand;
        break;
    case 4:
        result = value - item->operand;
        break;
    case 5:
        result = value * item->operand;
        break;
    case 6:
        result = _u32_div_f(value, item->operand);
        break;
    case 1:
        result = ~value;
        break;
    }
    WriteSessionPackedBits(item->bitOffset, item->bitCount, result);
    return TRUE;
}
