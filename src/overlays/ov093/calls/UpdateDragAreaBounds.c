#include "nitro/types.h"

typedef struct {
    s16 left;
    s16 top;
    s16 right;
    s16 bottom;
} Rect16;

typedef struct {
    int handle;
    int x;
    int y;
    u8 pad_0C[8];
    Rect16 bounds;
} SlotItem;

typedef struct {
    u8 pad_0000[0xcde8];
    SlotItem dragItem;
    u8 pad_ce04[0xd1c4 - 0xce04];
    int touchActive;
    u8 pad_d1c8[0xd1ec - 0xd1c8];
    Rect16 dragBounds;
} SceneWork;

extern SceneWork *data_ov093_020c5100;
extern void RuntimeState_SetCondition(int value);

void UpdateDragAreaBounds(void)
{
    SceneWork *work = data_ov093_020c5100;
    SlotItem *item;
    Rect16 *drag;

    work->touchActive = 0;
    RuntimeState_SetCondition(0);
    drag = &data_ov093_020c5100->dragBounds;
    item = &work->dragItem;
    drag->right = item->x + item->bounds.right;
    drag->bottom = item->y + item->bounds.bottom;
    drag->left = item->x + item->bounds.left;
    drag->top = item->y + item->bounds.top;
}
