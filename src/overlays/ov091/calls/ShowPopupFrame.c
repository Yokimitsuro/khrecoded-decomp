#include "nitro/types.h"

typedef struct {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u8 pad_08[8];
} TextFrame;

typedef struct {
    s32 state;
    u32 flags;
    s32 stateTimer;
    s32 x;
    s32 y;
    s32 param;
    u8 textLayer[0x34];
    u16 *text;
    TextFrame frame;
} PopupWindow;

typedef struct {
    u8 pad_00[0x10];
    int frameSlot;
} PopupManager;

extern PopupManager *data_ov091_020c375c;
extern void DrawPopupText(PopupWindow *window);
extern int GetNestedModeByte(void *layer);
extern void SetPopupSlotPos(int slotIndex, int x, int y, int offsetX, int offsetY);
extern void SetPopupSlotVisible(int slotIndex, BOOL visible);
extern void SetPopupState(PopupWindow *window, s32 state);

void ShowPopupFrame(PopupWindow *window)
{
    int lineHeight;

    DrawPopupText(window);
    lineHeight = GetNestedModeByte(window->textLayer);
    SetPopupSlotPos(data_ov091_020c375c->frameSlot, (window->frame.x + window->frame.width) * 8,
                             (window->frame.y + window->frame.height) * 8 + lineHeight / 2 - 4, window->x, window->y);
    SetPopupSlotVisible(data_ov091_020c375c->frameSlot, TRUE);
    SetPopupState(window, 5);
}
