#include "nitro/types.h"

extern BOOL func_ov095_020c1080(void *viewer);
extern void func_ov095_020bfa38(int mode, void *viewer);
extern BOOL PlaySoundEffect(int seqArcNo, int index);

void ShowPreviousEntry(void *viewer)
{
    if (!func_ov095_020c1080(viewer)) {
        return;
    }
    func_ov095_020bfa38(1, viewer);
    PlaySoundEffect(0, 0);
}
