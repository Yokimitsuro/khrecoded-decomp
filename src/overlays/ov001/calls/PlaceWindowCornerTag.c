#include "nitro/types.h"

typedef struct MessageWindow {
    u8 pad_00[0xc];
    BOOL hasBorder;
    u16 x;
    u16 y;
    u16 width;
    u16 height;
} MessageWindow;

extern void *GetSceneTagTracker(void);
extern int FindLoadedElementById(void *tracker, int tag);
extern void func_ov027_020b8514(void *tracker, int entry, s16 x, s16 y);
extern void func_ov027_020b8408(void *tracker, int entry, int visible);

void PlaceWindowCornerTag(MessageWindow *window)
{
    void *tracker = GetSceneTagTracker();
    int margin = 0;
    int x;
    int y;
    int entry;

    if (window->hasBorder) {
        margin = 7;
    }
    x = window->x + window->width - margin - 3;
    y = window->y + window->height - 1;
    entry = FindLoadedElementById(tracker, 5);
    func_ov027_020b8514(tracker, entry, x, y);
    func_ov027_020b8408(tracker, entry, 1);
}
