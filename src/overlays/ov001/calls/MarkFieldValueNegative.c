#include "nitro/types.h"

typedef struct FieldState {
    u8 pad_0000[0x20e];
    s16 currentValue;
    u8 pad_0210[4];
    u32 valueFlags;
} FieldState;

extern FieldState *data_ov001_020a0480;

void MarkFieldValueNegative(void)
{
    FieldState *field = data_ov001_020a0480;

    field->valueFlags |= 0x40;
    field->currentValue = -3;
}
