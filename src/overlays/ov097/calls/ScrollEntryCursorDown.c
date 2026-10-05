#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x2c];
    s32 scrollRow;
    s32 cursorRow;
    u8 pad_34[0x18];
} ScrollList;

typedef struct {
    u8 pad_000[0x3e8];
    int detailId;
    u8 pad_3ec[0x414 - 0x3ec];
} EntryLayout;

typedef struct {
    u32 values[2];
    int detailId;
    u32 rest[8];
} DetailRequest;

typedef struct {
    s32 selectedEntry;
    BOOL unk_04;
    u8 pad_008[0x180 - 0x8];
    ScrollList lists[2];
    u8 pad_218[0xce08 - 0x218];
    EntryLayout layouts[1];
    u8 pad_d21c[0xf064 - 0xd21c];
    BOOL isTouchScrolling;
    s32 scrollOffsetY;
    u8 pad_f06c[0xf0c4 - 0xf06c];
    BOOL isScrollEasing;
} MenuScene;

extern MenuScene *data_ov097_020c2540;
extern DetailRequest data_ov097_020c1f10;
extern BOOL StepListCursorDown(int listIndex, MenuScene *scene);
extern void func_ov097_020c0314(DetailRequest *request, MenuScene *scene);
extern void ResetScrollTrack(int trackIndex);
extern void func_ov097_020bfb58(int listIndex, MenuScene *scene);
extern BOOL IsEntryFlagSet_020c1494(int flagSet, int entryIndex);
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern void func_ov097_020c1578(int listIndex, MenuScene *scene);

void ScrollEntryCursorDown(MenuScene *scene)
{
    DetailRequest request;
    s32 selectedEntry;
    int entryIndex;

    if (!scene->unk_04 && !scene->isTouchScrolling) {
        if (!StepListCursorDown(0, scene)) {
            return;
        }
        entryIndex = scene->lists[0].scrollRow + scene->lists[0].cursorRow;
        scene->selectedEntry = entryIndex;
        request = data_ov097_020c1f10;
        request.detailId = scene->layouts[entryIndex].detailId;
        func_ov097_020c0314(&request, scene);
        ResetScrollTrack(1);
        data_ov097_020c2540->isScrollEasing = FALSE;
        scene->scrollOffsetY = 0;
        func_ov097_020bfb58(1, scene);
        PlaySoundEffect(0, 0);
        func_ov097_020c1578(1, scene);
        return;
    }
    if (!StepListCursorDown(1, scene)) {
        return;
    }
    scene->scrollOffsetY = scene->lists[1].scrollRow * -16;
    selectedEntry = scene->selectedEntry;
    ResetScrollTrack(1);
    data_ov097_020c2540->isScrollEasing = FALSE;
    func_ov097_020bfb58(1, scene);
    if (IsEntryFlagSet_020c1494(0, selectedEntry) && !scene->isTouchScrolling) {
        PlaySoundEffect(0, 0);
    }
}
