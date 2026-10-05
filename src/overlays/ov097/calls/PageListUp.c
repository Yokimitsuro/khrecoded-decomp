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
BOOL PageListUp(int listIndex, MenuScene *scene)
{
    ListCursor *cursor = &scene->cursors[listIndex];
    int top;

    if (cursor->scrollTop == 0) {
        return FALSE;
    }
    top = cursor->scrollTop - cursor->visibleCount;
    if (cursor->slotIndex < 0) {
        cursor->selected = 0;
    }
    if (top < 0) {
        cursor->scrollTop = 0;
    } else {
        cursor->scrollTop = top;
    }
    func_ov097_020c08d4(cursor->listId, scene);
    return TRUE;
}