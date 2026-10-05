#include "nitro/types.h"

typedef struct ValueMap {
    int values[3];
} ValueMap;

typedef struct MovieMenu {
    u8 pad_00[0x32];
    u8 rowCount;
} MovieMenu;

extern ValueMap data_ov035_020bc428;

int RemapMovieMenuValue(MovieMenu *menu, int value)
{
    ValueMap map = data_ov035_020bc428;

    if (menu->rowCount > 1) {
        value = map.values[value];
    }
    return value;
}