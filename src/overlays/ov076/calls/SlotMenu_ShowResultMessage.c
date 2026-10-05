#include "nitro/types.h"

typedef struct SlotMenu SlotMenu;

typedef struct MenuCallback {
    void (*handler)(SlotMenu *menu);
    SlotMenu *context;
} MenuCallback;

typedef union PanelSize {
    u32 packed;
    struct {
        u16 width;
        u16 height;
    } dim;
} PanelSize;

struct SlotMenu {
    u8 pad_00000[0x4e80];
    int messageTable[3];
    u8 pad_04E8C[0x7fc0 - 0x4e8c];
    u8 panel[0x11c04 - 0x7fc0];
    MenuCallback onCancel;
    u8 pad_11C0C[8];
    MenuCallback onConfirm;
    u16 buttonStates[4];
    u8 pad_11C24[0x49860 - 0x11c24];
    s32 resultType;
    u32 resultValue;
    u8 pad_49868[0x4a074 - 0x49868];
    s32 showTutorial;
    u8 pad_4A078[0x4a084 - 0x4a078];
    char formatBuffer[0x40];
};

extern u8 data_ov076_020cd2e0[];

extern BOOL IsGlobalPackedBitSet(int bitIndex);
extern void *func_ov027_020ba2c8(int *table, int index);
extern void *func_ov027_020ba300(int *table, int index, char *buffer, int size, ...);
extern PanelSize func_ov076_020cb2d8(void *panel, int owner, void *message);
extern void MenuPanel_InitStandard(void *panel, int owner, int x, int y, u16 width, u16 height, void *message);
extern void func_ov076_020c8198(SlotMenu *menu, int mode);
extern void SlotMenu_OnMessageConfirm(SlotMenu *menu);
extern void SlotMenu_OpenSlotPanel(SlotMenu *menu);
extern void func_ov076_020c4ec8(SlotMenu *menu);

void SlotMenu_ShowResultMessage(SlotMenu *menu, u16 y)
{
    int messageId = -1;
    BOOL seen = IsGlobalPackedBitSet(0xf7d);
    BOOL firstTime = TRUE;
    void *message;
    PanelSize size;
    MenuCallback confirm;

    if (seen) {
        firstTime = FALSE;
    }
    switch (menu->resultType) {
    case 4:
        message = func_ov027_020ba300(menu->messageTable, 0x57, menu->formatBuffer, 0x40, menu->resultValue);
        break;
    case 3:
        messageId = 0x56;
        break;
    case 2:
        messageId = 0x55;
        break;
    case 1:
        messageId = 0x54;
        break;
    case 0:
    default:
        firstTime = FALSE;
        message = func_ov027_020ba300(menu->messageTable, 0x53, menu->formatBuffer, 0x40, menu->resultValue);
        break;
    }
    if (messageId >= 0) {
        message = func_ov027_020ba2c8(menu->messageTable, messageId);
    }
    size = func_ov076_020cb2d8(menu->panel, 1, message);
    menu->buttonStates[0] = 1;
    menu->buttonStates[1] = 1;
    menu->buttonStates[2] = 1;
    menu->buttonStates[3] = 3;
    confirm.handler = SlotMenu_OnMessageConfirm;
    confirm.context = menu;
    menu->onConfirm = confirm;
    if (firstTime) {
        MenuCallback cancel;
        cancel.handler = SlotMenu_OpenSlotPanel;
        cancel.context = menu;
        menu->onCancel = cancel;
        if (!IsGlobalPackedBitSet(data_ov076_020cd2e0[0xc] + 0xf50)) {
            menu->showTutorial = 1;
        }
    } else {
        MenuCallback cancel;
        cancel.handler = func_ov076_020c4ec8;
        cancel.context = menu;
        menu->onCancel = cancel;
    }
    MenuPanel_InitStandard(menu->panel, 1, 0, y, size.dim.width, size.dim.height, message);
    func_ov076_020c8198(menu, 0);
}
