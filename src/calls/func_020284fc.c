#include "nitro/types.h"

extern u32 func_ov001_02063838(void);
extern BOOL IsActorCountNonzero(void);
extern s32 func_ov001_02063a38(void);
extern BOOL func_ov036_020bc668(void);

BOOL func_020284fc(void)
{
    if (func_ov001_02063838() != 0 && IsActorCountNonzero() != 0) {
        return TRUE;
    }
    if (func_ov001_02063a38() == 8 && func_ov036_020bc668() != 0) {
        return TRUE;
    }
    return FALSE;
}
