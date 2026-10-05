#include "nitro/types.h"

extern void *func_ov039_020bc1dc(void);
extern void func_ov027_020b91e8(void *scene, void *node, int *offset, int flags);

typedef struct {
    u8 pad0[0x24];
    void *cursorNode;
    u8 pad28[0x5d0 - 0x28];
    int cursor;
} MenuState;

void PlaceCursorNode(MenuState *menu)
{
    int offset[2];

    offset[0] = (menu->cursor * 0x1c) << 12;
    offset[1] = 0;
    func_ov027_020b91e8(func_ov039_020bc1dc(), menu->cursorNode, offset, 3);
}
