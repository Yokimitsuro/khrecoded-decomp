#include "nitro/types.h"

typedef struct {
    int listId;
    int visibleCount;
    int totalCount;
    int slotIndex;
    u8 pad_10[0x1c];
    int scrollTop;
    int selected;
    u8 pad_34[0x18];
} ListCursor;

typedef struct {
    u8 pad_000[0x180];
    ListCursor cursors[2];
} MenuScene;

extern void func_ov097_020c08d4(int listId, MenuScene *scene);
BOOL PageListDown(int listIndex, MenuScene *scene)
{
    ListCursor *cursor = &scene->cursors[listIndex];
    int top = cursor->scrollTop;

    if (top == cursor->totalCount - cursor->visibleCount) {
        return FALSE;
    }
    top += cursor->visibleCount;
    if (cursor->slotIndex < 0) {
        cursor->selected = cursor->visibleCount - 1;
    }
    if (top > cursor->totalCount - cursor->visibleCount) {
        cursor->scrollTop = cursor->totalCount - cursor->visibleCount;
    } else {
        cursor->scrollTop = top;
    }
    func_ov097_020c08d4(cursor->listId, scene);
    return TRUE;
}