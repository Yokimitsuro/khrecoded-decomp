#include "nitro/types.h"

typedef struct {
    int state;
    u32 flags;
    int frameCount;
    int textId;
    int textArg;
    u8 pad_14[4];
    u8 textBox[0x38];
    u16 tileX;
    u16 tileY;
    u16 offsetX;
    u16 offsetY;
} PopupState;

typedef struct {
    u8 pad_00[0x10];
    int slotIndex;
} PopupManager;

extern PopupManager *data_ov093_020c5104;
extern void DrawPopupText_020c2e24(PopupState *popup);
extern int GetNestedModeByte(void *textBox);
extern void SetPopupPosition(int slotIndex, int x, int y, int textId, int textArg);
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern void func_ov093_020c319c(int slotIndex, BOOL visible);
extern void StateMachine_SetState(PopupState *machine, int state);

void OpenPopupWindow_020c3438(PopupState *popup)
{
    int lineHeight;

    DrawPopupText_020c2e24(popup);
    lineHeight = GetNestedModeByte(popup->textBox);
    SetPopupPosition(data_ov093_020c5104->slotIndex, (popup->tileX + popup->offsetX) * 8,
                        (popup->tileY + popup->offsetY) * 8 + lineHeight / 2 - 4, popup->textId, popup->textArg);
    PlaySoundEffect(0, 9);
    func_ov093_020c319c(data_ov093_020c5104->slotIndex, TRUE);
    StateMachine_SetState(popup, 5);
}
