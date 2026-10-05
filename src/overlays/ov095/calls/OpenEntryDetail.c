#include "nitro/types.h"

typedef struct {
    u8 pad_00000[0x11108];
    int detailOpen;
    u8 pad_1110C[0x14];
    int hasDetail;
} EntryViewer;

extern void func_ov095_020bfa38(int mode, EntryViewer *viewer);
extern BOOL PlaySoundEffect(int seqArcNo, int index);

void OpenEntryDetail(EntryViewer *viewer)
{
    if (viewer->detailOpen != FALSE) {
        return;
    }
    if (viewer->hasDetail == 0) {
        return;
    }
    viewer->detailOpen = TRUE;
    func_ov095_020bfa38(1, viewer);
    PlaySoundEffect(0, 2);
}
