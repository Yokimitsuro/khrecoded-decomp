#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x2c];
    int scrollTop;
    int cursorRow;
    u8 pad_34[0x4c - 0x34];
} ListState;

typedef struct {
    u8 pad_0000[0xcf04];
    int selectedEntry;
    u8 pad_cf08[0xd054 - 0xcf08];
    ListState lists[1];
} ViewerWork;

extern BOOL StepListCursorUp(int listIndex, ViewerWork *work);
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern void func_ov099_020c158c(ViewerWork *work);
extern void func_ov099_020bf838(int listIndex, ViewerWork *work);
extern void SetViewerMode(int mode, ViewerWork *work);

void HandleListCursorUp(ViewerWork *work)
{
    ListState *list;

    if (!StepListCursorUp(0, work)) {
        return;
    }
    list = &work->lists[0];
    work->selectedEntry = list->scrollTop + list->cursorRow;
    PlaySoundEffect(0, 0);
    func_ov099_020c158c(work);
    func_ov099_020bf838(0, work);
    SetViewerMode(1, work);
}
