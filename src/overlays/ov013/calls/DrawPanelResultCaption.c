#include "nitro/types.h"

typedef struct TextRect {
    int width;
    int height;
} TextRect;

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
    u8 pad_00[0x18];
    u8 window[0x2f0 - 0x18];
    s8 progress;
} MenuState;

extern MenuState *data_ov013_02074ce0;
extern char data_ov013_02074c70[];
extern char data_ov013_02074c80[];
extern char data_ov013_02074c94[];
extern char data_ov013_02074cac[];
extern char data_ov013_02074cc4[];

extern void func_ov002_020620fc(int selector);
extern void MIi_CpuClear16(int value, void *dst, int size);
extern int DispatchContextCommand(int command, int value, int extra, void *buffer);
extern s32 func_ov013_02070cb4(void);
extern char *func_ov002_020621c4(int index, int extra);
extern void *OS_SNPrintf_0202e094(char *dst, unsigned int len, const char *fmt, ...);
extern u32 GetLanguageIndex(void);
extern void ActivatePanelSlotCD_02061a68(int a, int b, int c, int d, int e, char *text);
extern void ActivatePanelSlotCD(int layer, int x, int y, int color, const void *text);
extern TextRect func_ov002_02062890(int which, const void *text);
extern int *FindWidgetById(void *entries, int index);
extern void SetEntrySlotsVisible(void *entries, int *slot, int visible);

void DrawPanelResultCaption(int mode)
{
    u16 text[0x40] = {0};
    u16 title[0x40] = {0};
    PanelInfo info;
    TextRect rect;
    char *label;
    char *count;
    MenuWindow *window;

    func_ov002_020620fc(0);
    MIi_CpuClear16(0, text, sizeof(text));
    if ((data_ov013_02074ce0->progress + 1) % 10 != 0) {
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
    } else {
        window = (MenuWindow *)data_ov013_02074ce0->window;
        SetEntrySlotsVisible(window->slots, FindWidgetById(window->slots, 6), 0);
    }

    switch (mode) {
    case 0: {
        u16 stage[0x20] = {0};

        OS_SNPrintf_0202e094((char *)stage, 0x20, func_ov002_020621c4(0x3f, 0), data_ov013_02074ce0->progress + 1);
        ActivatePanelSlotCD(0, 0x1e, 0x49, 2, stage);
        rect = func_ov002_02062890(0, func_ov002_020621c4(0x20, 0));
        ActivatePanelSlotCD(0, 0x41 - rect.width / 2, 0x62, 2, func_ov002_020621c4(0x20, 0));
        rect = func_ov002_02062890(0, func_ov002_020621c4(0x21, 0));
        ActivatePanelSlotCD(0, 0xad - rect.width / 2, 0x62, 2, func_ov002_020621c4(0x21, 0));
        break;
    }
    case 1:
        ActivatePanelSlotCD(0, 0x1e, 0x49, 2, func_ov002_020621c4(0x23, 0));
        rect = func_ov002_02062890(0, func_ov002_020621c4(0x3c, 0));
        ActivatePanelSlotCD(0, 0x41 - rect.width / 2, 0x62, 2, func_ov002_020621c4(0x3c, 0));
        rect = func_ov002_02062890(0, func_ov002_020621c4(0x3d, 0));
        ActivatePanelSlotCD(0, 0xad - rect.width / 2, 0x62, 2, func_ov002_020621c4(0x3d, 0));
        break;
    case 2:
        ActivatePanelSlotCD(0, 0x1e, 0x49, 2, func_ov002_020621c4(0x22, 0));
        rect = func_ov002_02062890(0, func_ov002_020621c4(0x3c, 0));
        ActivatePanelSlotCD(0, 0x41 - rect.width / 2, 0x62, 2, func_ov002_020621c4(0x3c, 0));
        rect = func_ov002_02062890(0, func_ov002_020621c4(0x3d, 0));
        ActivatePanelSlotCD(0, 0xad - rect.width / 2, 0x62, 2, func_ov002_020621c4(0x3d, 0));
        break;
    }
}
