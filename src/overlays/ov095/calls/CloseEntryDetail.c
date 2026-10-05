#include "nitro/types.h"

typedef struct {
    u8 pad_00000[0x11108];
    int detailOpen;
} EntryViewer;

extern void func_ov095_020bfa38(int mode, EntryViewer *viewer);
extern BOOL PlaySoundEffect(int seqArcNo, int index);

void CloseEntryDetail(EntryViewer *viewer)
{
    if (viewer->detailOpen != TRUE) {
        return;
    }
    viewer->detailOpen = FALSE;
    func_ov095_020bfa38(1, viewer);
    PlaySoundEffect(0, 2);
}
