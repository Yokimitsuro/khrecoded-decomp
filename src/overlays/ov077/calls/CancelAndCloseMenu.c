#include "nitro/types.h"

extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern void func_ov077_020c6cb0(void *work, BOOL restoreElements);

int CancelAndCloseMenu(void *work)
{
    PlaySoundEffect(1, 3);
    func_ov077_020c6cb0(work, TRUE);
    return 3;
}
