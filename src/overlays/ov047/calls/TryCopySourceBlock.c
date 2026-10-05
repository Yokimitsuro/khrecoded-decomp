#include "nitro/types.h"

extern u32 func_ov001_0207b3f4(void);
extern int func_ov027_020b9f9c(void *dest);

BOOL TryCopySourceBlock(void *dest)
{
    BOOL canCopy;

    if (func_ov001_0207b3f4() == 1 || func_ov001_0207b3f4() == 0) {
        canCopy = TRUE;
    } else {
        canCopy = FALSE;
    }
    if (!canCopy) {
        return FALSE;
    }
    func_ov027_020b9f9c(dest);
    return TRUE;
}
