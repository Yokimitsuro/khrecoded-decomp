#include "nitro/types.h"

extern int data_ov001_020a04f0;
extern BOOL func_ov001_0207e0bc(void);
extern void func_ov001_0207d71c(void);

BOOL TryFinishPendingTask(void)
{
    BOOL finished = FALSE;

    if (data_ov001_020a04f0 == 0) {
        return finished;
    }
    if (func_ov001_0207e0bc()) {
        func_ov001_0207d71c();
        finished = TRUE;
    }
    return finished;
}
