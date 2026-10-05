#include "nitro/types.h"

extern int func_ov001_02064784(void);
extern BOOL func_ov001_020645c8(u32 value);

BOOL IsModeSetOrFlag370aClear(void) {
    if (func_ov001_02064784() != 0 || !func_ov001_020645c8(0x370a)) {
        return TRUE;
    }
    return FALSE;
}
