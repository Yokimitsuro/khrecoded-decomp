#include "nitro/types.h"

typedef struct PanelInfo {
    u8 header[0x10];
    char name[0x58];
    u8 kind;
    u8 pad_69[7];
} PanelInfo;

typedef struct MenuWindow {
    u8 pad_00[0x6800];
    u8 slots[0x100];
} MenuWindow;

typedef struct MenuState {
    s8 mode;
    u8 pad_01[0x17];
    u8 window[0x80];
    u8 flags98;
    u8 pad_99;
    u8 lowBits9a : 3;
    u8 hidden9a : 1;
    u8 highBits9a : 4;
    u8 pad_9b[0x255];
    s8 progress;
} MenuState;

extern MenuState *data_ov013_02074ce0;
extern char data_ov013_02074c70[];
extern char data_ov013_02074c80[];
extern char data_ov013_02074c94[];
extern char data_ov013_02074cac[];
extern char data_ov013_02074cc4[];

extern void func_ov002_020620fc(int selector);
extern void MI_CpuFill8(void *dst, int value, int size);
extern int DispatchContextCommand(int command, int value, int extra, void *buffer);
extern s32 func_ov013_02070cb4(void);
extern char *func_ov002_020621c4(int index, int extra);
extern void *OS_SNPrintf_0202e094(char *dst, unsigned int len, const char *fmt, ...);
extern u32 GetLanguageIndex(void);
extern void ActivatePanelSlotCD_02061a68(int a, int b, int c, int d, int e, char *text);
extern void DrawPanelSlotCDText(int a, int b, int c, int d, int e, int f, int g, char *text);
extern int *FindWidgetById(void *entries, int index);
extern void SetEntrySlotsVisible(void *entries, int *slot, int visible);

void RefreshProgressCaption(void) {
    u16 text[0x40] = {0};
    u16 title[0x40] = {0};
    PanelInfo info;
    char *label;
    char *count;
    MenuState *state;
    MenuWindow *window;

    func_ov002_020620fc(-1);
    MI_CpuFill8(text, 0, sizeof(text));
    if ((data_ov013_02074ce0->progress + 1) % 10 != 0) {
        if (DispatchContextCommand(1, 0, 0, 0)) {
            DispatchContextCommand(0, func_ov013_02070cb4(), 0, &info);
            OS_SNPrintf_0202e094((char *)title, 0x40, func_ov002_020621c4(0x1e, 0), info.name);
            switch (GetLanguageIndex()) {
            case 3:
                label = func_ov002_020621c4(info.kind + 0x18, 0);
                count = func_ov002_020621c4(0x1f, 0);
                OS_SNPrintf_0202e094((char *)text, 0x40, data_ov013_02074c70, (char *)title, label, count);
                break;
            case 1:
                label = func_ov002_020621c4(info.kind + 0x18, 0);
                count = func_ov002_020621c4(0x1f, 0);
                OS_SNPrintf_0202e094((char *)text, 0x40, data_ov013_02074c80, (char *)title, label, count);
                break;
            case 2:
                count = func_ov002_020621c4(0x1f, 0);
                label = func_ov002_020621c4(info.kind + 0x18, 0);
                OS_SNPrintf_0202e094((char *)text, 0x40, data_ov013_02074c80, count, label, (char *)title);
                break;
            case 5:
                count = func_ov002_020621c4(0x1f, 0);
                label = func_ov002_020621c4(info.kind + 0x18, 0);
                OS_SNPrintf_0202e094((char *)text, 0x40, data_ov013_02074c94, count, label, (char *)title);
                break;
            case 4:
                count = func_ov002_020621c4(0x1f, 0);
                label = func_ov002_020621c4(info.kind + 0x18, 0);
                OS_SNPrintf_0202e094((char *)text, 0x40, data_ov013_02074cac, count, label, (char *)title);
                break;
            case 0:
            default:
                label = func_ov002_020621c4(info.kind + 0x18, 0);
                count = func_ov002_020621c4(0x1f, 0);
                OS_SNPrintf_0202e094((char *)text, 0x40, data_ov013_02074cc4, (char *)title, label, count);
                break;
            }
            ActivatePanelSlotCD_02061a68(0, 0x46, 2, 2, 6, (char *)text);
            state = data_ov013_02074ce0;
            if (!state->hidden9a) {
                if (state->mode != 6 && state->mode != 7) {
                    DrawPanelSlotCDText(1, 0xb4, 0xb5, 0x4b, 10, 2, 0x480, func_ov002_020621c4(0x74, 0));
                }
                window = (MenuWindow *)data_ov013_02074ce0->window;
                SetEntrySlotsVisible(window->slots, FindWidgetById(window->slots, 6), 1);
            } else {
                window = (MenuWindow *)state->window;
                SetEntrySlotsVisible(window->slots, FindWidgetById(window->slots, 6), 0);
            }
        }
    } else {
        window = (MenuWindow *)data_ov013_02074ce0->window;
        SetEntrySlotsVisible(window->slots, FindWidgetById(window->slots, 6), 0);
    }
    data_ov013_02074ce0->flags98 |= 2;
}
