#include "nitro/types.h"

int MapCodeToSlotIndex(int code)
{
    int slot = -1;
    switch (code) {
    case 5:    slot = 0; break;
    case 0xd:  slot = 1; break;
    case 0x18: slot = 2; break;
    case 0x19: slot = 3; break;
    case 0xa:  slot = 4; break;
    }
    return slot;
}
