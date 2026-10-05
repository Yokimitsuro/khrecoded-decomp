#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ValueEntry {
    fx32 value;
    u8 pad_04[0x1c];
} ValueEntry;

typedef struct ValueOwner {
    u8 pad_00[0xa];
    u8 type;
    u8 pad_0B[0x9d];
    ValueEntry entries[1];
} ValueOwner;

extern int FX_Mul(int left, int right);

fx32 GetEntryScaledValue(ValueOwner *owner, int index)
{
    fx32 value = owner->entries[index - 1].value;

    if (owner->type == 3) {
        value = FX_Mul(value, 0x1000);
    }
    return value;
}
