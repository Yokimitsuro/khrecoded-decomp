#include "nitro/types.h"

typedef struct FlagValues {
    int values[6];
} FlagValues;

extern const FlagValues data_02055af8;
extern u8 *data_0205fe0c;

int GetFlagTableValue(void)
{
    FlagValues table = data_02055af8;

    return table.values[(u16)(data_0205fe0c[0x2c66] & 7)];
}
