#include "nitro/types.h"

typedef struct FieldValueState {
    u8 pad_00[2];
    s16 defaultValue;
    u8 pad_04[2];
    s16 currentValue;
    s16 pendingValue;
} FieldValueState;

typedef struct FieldState {
    u8 pad_0000[0x208];
    FieldValueState value;
} FieldState;

extern FieldState *data_ov001_020a0480;

void SetPendingFieldValue(s16 value)
{
    FieldValueState *state = &data_ov001_020a0480->value;

    if (state->pendingValue == -1) {
        state->pendingValue = value;
    }
}
