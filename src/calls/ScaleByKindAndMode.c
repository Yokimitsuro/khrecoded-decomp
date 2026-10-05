#include "nitro/types.h"

typedef struct ScaleTable {
    s32 rates[2][4];
} ScaleTable;

typedef struct GameSettings {
    u8 pad[0x2878];
    u32 mode : 2;
} GameSettings;

extern GameSettings *data_0205fe0c;
extern const ScaleTable data_02055a58;

s32 ScaleByKindAndMode(int kind, s32 value)
{
    u32 mode = data_0205fe0c->mode;
    ScaleTable table = data_02055a58;
    /* Only kinds 1 and 2 are scaled */
    switch (kind) {
    case 1:
    case 2:
        value = (value * table.rates[kind - 1][mode] + 0xfff) >> 12;
        break;
    }
    return value;
}

