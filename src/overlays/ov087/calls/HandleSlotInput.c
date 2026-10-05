#include "nitro/types.h"

typedef struct {
    int kind;
    int unk_04;
} PanelMode;

typedef struct {
    u8 pad_000[0xc];
    int scrollActive;
    u8 pad_010[0xb60];
    PanelMode modes[6];
    int modeIndex;
    int selectedSlot;
} PanelScene;

extern PanelScene *func_ov039_020bc638(void);
extern void func_ov087_020c44c4(PanelScene *scene, void *context);
extern void MoveCursorToWidget(PanelScene *scene, void *context, int slot, BOOL immediate);

void HandleSlotInput(void *context, u32 pressed)
{
    PanelScene *scene = func_ov039_020bc638();
    BOOL immediate = FALSE;

    if (!(pressed & 0xf0)) {
        return;
    }
    if (scene->scrollActive != 0) {
        return;
    }
    if (pressed & 0xc0) {
        immediate = TRUE;
        func_ov087_020c44c4(scene, context);
    } else if (scene->selectedSlot != 0) {
        immediate = TRUE;
    }
    MoveCursorToWidget(scene, context, scene->selectedSlot, immediate);
}
