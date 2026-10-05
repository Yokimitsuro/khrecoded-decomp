#include "nitro/types.h"

typedef struct ScreenSprite {
    s32 x;
    s32 y;
    s32 unk_08;
    s32 animIndex;
    s32 unk_10;
    s32 spriteIndex;
} ScreenSprite;

typedef struct ItemScreen {
    u8 pad_00000[0x14];
    u8 work[0x11ebc];
    s32 mode;
    ScreenSprite sprites[12];
    s32 state;
} ItemScreen;

extern s8 data_ov077_020ca11c[];
extern int func_02029f5c(void);
extern void *func_ov039_020bc1dc(void);
extern void SetModeTwoAndRefresh(ItemScreen *screen);
extern BOOL func_ov077_020c8bf4(void *work, void *owner, BOOL (*predicate)(void *owner),
                                void (*onClose)(ItemScreen *screen), const s8 *message, int arg);
extern void ShowSlotHeaderMessage(ItemScreen *screen);
extern void UpdateItemScreenDisplay(ItemScreen *screen);
extern void SetFlagGatedElementsVisible(void *container, BOOL visible);

void OpenHelpMessageOrActivate(ItemScreen *screen)
{
    if (func_02029f5c() != 0) {
        return;
    }
    if (!func_ov077_020c8bf4(screen->work, screen, NULL, SetModeTwoAndRefresh, data_ov077_020ca11c, 1)) {
        screen->state = 2;
        ShowSlotHeaderMessage(screen);
        UpdateItemScreenDisplay(screen);
        return;
    }
    screen->state = 1;
    SetFlagGatedElementsVisible(func_ov039_020bc1dc(), FALSE);
}
