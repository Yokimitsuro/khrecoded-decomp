#include "nitro/types.h"

extern BOOL SelectNextGridRow(void *viewer);
extern void func_ov095_020bfa38(int mode, void *viewer);
extern BOOL PlaySoundEffect(int seqArcNo, int index);

void ShowNextEntry(void *viewer)
{
    if (!SelectNextGridRow(viewer)) {
        return;
    }
    func_ov095_020bfa38(1, viewer);
    PlaySoundEffect(0, 0);
}
