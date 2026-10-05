#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x2c];
    s32 scrollRow;
    u8 pad_30[0x1c];
} ScrollList;

typedef struct {
    s32 selectedEntry;
    BOOL unk_04;
    u8 pad_008[0x180 - 0x8];
    ScrollList lists[2];
    u8 pad_218[0xf064 - 0x218];
    BOOL isTouchScrolling;
    s32 scrollOffsetY;
    u8 pad_f06c[0xf0c4 - 0xf06c];
    BOOL isScrollEasing;
} MenuScene;

extern MenuScene *data_ov097_020c2540;
extern BOOL PageListDown(int listIndex, MenuScene *scene);
extern void ResetScrollTrack(int trackIndex);
extern void func_ov097_020bfb58(int listIndex, MenuScene *scene);
extern BOOL IsEntryFlagSet_020c1494(int flagSet, int entryIndex);
extern BOOL PlaySoundEffect(int seqArcNo, int index);

void ScrollEntryListDown(MenuScene *scene)
{
    s32 selectedEntry;

    if (!scene->unk_04 && !scene->isTouchScrolling) {
        return;
    }
    if (!PageListDown(1, scene)) {
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
