#include "nitro/types.h"

typedef struct ListView {
    u8 pad_00[0x94];
    int scrollX;
    int targetX;
    BOOL scrolling;
    u8 pad_a0[4];
    int cursorIndex;
    int selectedIndex;
} ListView;

extern void func_ov073_020c3908(ListView *list);
extern void HandleListCursorInput(ListView *list, int input);
extern void SelectListEntry(ListView *list, int entryIndex);
extern void PlaceCursorAtListEntry(ListView *list, int entryIndex);

void UpdateListScroll(ListView *list, BOOL refresh, int input)
{
    int delta;
    int distance;

    if (refresh) {
        func_ov073_020c3908(list);
    }
    HandleListCursorInput(list, input);
    if (list->scrolling) {
        delta = list->targetX - list->scrollX;
        distance = delta < 0 ? -delta : delta;
        if (distance < 40) {
            list->scrollX = list->targetX;
            list->scrolling = FALSE;
        } else {
            list->scrollX += delta / (delta < 0 ? -delta : delta) * 40;
        }
        SelectListEntry(list, list->selectedIndex);
        PlaceCursorAtListEntry(list, list->cursorIndex);
    }
}
