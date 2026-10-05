#include "nitro/types.h"

typedef struct SessionInfo {
    u32 unk_00;
    u16 checksum;
    u16 exitMode : 3;
    u16 showName : 1;
    u16 flagsRest : 12;
    u8 stage;
    u8 world;
} SessionInfo;

typedef struct PanelState {
    u8 pad_00[0x18];
    char playerName[1];
} PanelState;

extern PanelState *data_ov013_02074ce0;
extern SessionInfo data_0206085c;
extern char *func_ov002_020621c4(int index, int variant);
extern void DrawPanelSlotABText(int screen, int p2, int x, int y, int p5, int p6, int p7, const char *text);
extern void func_ov002_02061dc8(int screen, int p2, int x, int y, int p5, int p6, const u16 *text, int p8);
extern int OS_SNPrintf_0202e094(u16 *buffer, u32 size, const char *format, ...);

void DrawPanelHeaderTexts(void)
{
    DrawPanelSlotABText(0, 0, 2, 0xe6, 0x10, 10, 0x800, func_ov002_020621c4(0x3a, 0));
    if (data_0206085c.showName) {
        u16 nameText[64] = {0};

        OS_SNPrintf_0202e094(nameText, 0x40, func_ov002_020621c4(0x3b, 0), data_ov013_02074ce0->playerName);
        func_ov002_02061dc8(1, 0, 0x7a, 2, 6, 6, nameText, 0);
    }
    if (data_0206085c.world != data_0206085c.stage) {
        DrawPanelSlotABText(1, 0, 0x9a, 0x100, 0x10, 2, 0x411, func_ov002_020621c4(0x6a, 0));
    }
    DrawPanelSlotABText(1, 0, 0xae, 0x100, 0x10, 2, 0x411, func_ov002_020621c4(0x6b, 0));
}
