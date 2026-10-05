#include "nitro/types.h"

typedef struct {
    int id;
    int visibleRows;
    int totalRows;
    int panelIndex;
    u8 pad_10[0x1c];
    int topRow;
    int cursorRow;
    u8 pad_34[0x18];
} ScrollList;

typedef struct {
    int selectedEntry;
    u8 pad_04[0xcbcc];
    ScrollList lists[1];
} MenuScene;

extern BOOL func_ov091_020c1774(void);
extern BOOL ScrollListUp(int listIndex, MenuScene *scene);
extern BOOL IsEntryFlagSet(int flagSet, int entryIndex);
extern void SetEntryFlag(int flagSet, int entryIndex);
extern void SetListPanelSlotValue(int screen, int panelIndex, int value, MenuScene *scene);
extern BOOL PlaySoundEffect(int seqArcNo, int index);

void MoveEntryCursorUp(MenuScene *scene)
{
    ScrollList *list;
    int entry;

    if (func_ov091_020c1774()) {
        return;
    }
    if (!ScrollListUp(0, scene)) {
        return;
    }
    list = &scene->lists[0];
    entry = list->topRow + list->cursorRow;
    scene->selectedEntry = entry;
    if (IsEntryFlagSet(2, entry)) {
        SetEntryFlag(3, entry);
    }
    entry = scene->selectedEntry;
    SetListPanelSlotValue(0, entry + 1, IsEntryFlagSet(3, entry) ? TRUE : FALSE, scene);
    PlaySoundEffect(0, 0);
}
