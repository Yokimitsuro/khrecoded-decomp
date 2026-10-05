#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    u8 rowHeight;
    u8 pad_09[0x33];
    u8 rowCount;
    u8 pad_3d[3];
    void *upArrow;
    void *downArrow;
    void *frame;
    void *rows[32];
    int userA;
    int userB;
} ScrollList;

extern void *func_ov027_020b90c4(void *root, int id);
extern void func_ov039_020bdf30(ScrollList *list, void *root, int layout);

void InitScrollListWidgets(ScrollList *list, void *root, int arrowId, s16 rowId, u8 rowCount,
                                    int layout, int rowHeight, int userA, int userB)
{
    s16 i;
    s16 id = rowId;

    list->upArrow = func_ov027_020b90c4(root, arrowId);
    list->downArrow = func_ov027_020b90c4(root, arrowId + 1);
    id++;
    list->frame = func_ov027_020b90c4(root, rowId);
    for (i = 0; i < rowCount; i++) {
        list->rows[i] = func_ov027_020b90c4(root, id++);
    }
    list->rowHeight = rowHeight;
    list->rowCount = rowCount;
    list->userA = userA;
    list->userB = userB;
    func_ov039_020bdf30(list, root, layout);
}
