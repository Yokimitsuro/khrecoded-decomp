#include "nitro/types.h"

typedef struct MenuState {
    u8 unknown_00[0x2e];
    s16 level;
} MenuState;

extern MenuState *data_ov035_020bc500;

int GetScaledMenuLevel(int mode) {
    switch (mode) {
    case 0:
        return data_ov035_020bc500->level;
    case 1:
        return (data_ov035_020bc500->level * 130 + 50) / 100;
    case 2:
        return (data_ov035_020bc500->level * 115 + 50) / 100;
    }
    return -1;
}
