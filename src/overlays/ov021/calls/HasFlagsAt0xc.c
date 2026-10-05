#include "nitro/types.h"

typedef struct FlagHolder {
    u8 pad_00[0xc];
    u16 flagsA;
    u16 flagsB;
} FlagHolder;

BOOL HasFlagsAt0xc(FlagHolder *holder, u16 mask)
{
    BOOL result = FALSE;
    if (holder->flagsA & mask) {
        result = TRUE;
    }
    return result;
}
