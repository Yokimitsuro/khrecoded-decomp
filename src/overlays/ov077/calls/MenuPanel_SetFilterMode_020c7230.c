#include "nitro/types.h"

typedef struct MenuPanel {
    u8 pad_0000[0x18];
    void *container;
    u8 pad_001C[4];
    u16 filterMode;
    u8 pad_0022[0x4d78 - 0x22];
    u16 firstIndex;
    u8 pad_4D7A[0x4d84 - 0x4d7a];
    u16 topIndex;
    s16 cursorIndex;
    s16 lastCursorIndex;
} MenuPanel;

extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern u16 MenuPanel_ApplyCategoryFilter_020c6c68(MenuPanel *panel, int mode);
extern void *FindWidgetById(void *container, int elementId);
extern void func_ov027_020b96c0(void *container, void *element, u16 mode);
extern void func_ov077_020c6dec(MenuPanel *panel);

BOOL MenuPanel_SetFilterMode_020c7230(MenuPanel *panel, int mode)
{
    BOOL changed;

    if ((panel->filterMode != mode && MenuPanel_ApplyCategoryFilter_020c6c68(panel, mode) != 0) || mode == 1) {
        changed = TRUE;
    } else {
        changed = FALSE;
    }
    if (changed) {
        PlaySoundEffect(1, 2);
        panel->filterMode = mode;
        panel->topIndex = panel->firstIndex;
        panel->cursorIndex = 0;
        panel->lastCursorIndex = panel->cursorIndex;
        func_ov027_020b96c0(panel->container, FindWidgetById(panel->container, 0x1b), mode);
        func_ov077_020c6dec(panel);
    } else {
        PlaySoundEffect(1, 4);
    }
    return changed;
}

