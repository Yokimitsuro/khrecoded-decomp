#include "nitro/types.h"

typedef struct FlagHolder {
    u8 pad_00[0xc];
    u16 flagsA;
    u16 flagsB;
} FlagHolder;

BOOL HasFlagsAt0xe(FlagHolder *holder, u16 mask)
{
    BOOL result = FALSE;
    if (holder->flagsB & mask) {
        result = TRUE;
    }
    return result;
}
