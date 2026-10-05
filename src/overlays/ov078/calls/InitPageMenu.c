#include "nitro/types.h"

typedef struct PageMenu {
    void *bufferA;
    void *bufferB;
    void *bufferC;
    void *imageA;
    u8 pad_10[8];
    void *imageB;
    u8 pad_1c[0x5d0 - 0x1c];
    int cursor;
    int page;
} PageMenu;

typedef struct LayoutEntry {
    int start;
    u8 pad_04[8];
    int count;
    int stride;
    u8 pad_14[0x10];
} LayoutEntry;

extern PageMenu *data_ov078_020c51e0;
extern LayoutEntry data_ov078_020c5024[];
extern char sOv078_UiMenuQuestP2_020c5168[];
extern char sOv078_UiMenuLanguageQuestP2_020c517c[];
extern char sOv078_UiBtlStrLanguageP2_020c5190[];
extern char sOv078_UiMenuStrLanguageQstSZ_020c51a0[];
extern u8 *data_0205fe0c;

extern void MI_CpuFill8(void *dest, int value, u32 size);
extern void *Msg_OpenContainerAndReadHeader(const char *path, int heapId, int flags);
extern void LoadPackedFileView(void **out, const void *path, int flags);
extern void AcquireRecordManager(void);
extern void AcquireRecordSlot(int slot, int flags);
extern void func_ov078_020c43e0(PageMenu *menu);
extern void LoadPageMenuWidgets(PageMenu *menu);
extern void InitSequence(PageMenu *menu);

BOOL InitPageMenu(PageMenu *menu)
{
    int i;
    int cursor;

    MI_CpuFill8(menu, 0, sizeof(PageMenu));
    data_ov078_020c51e0 = menu;
    data_ov078_020c5024[0].start = 1;
    for (i = 1; i < 9; i++) {
        data_ov078_020c5024[i].start = data_ov078_020c5024[i - 1].start +
                                       data_ov078_020c5024[i - 1].count * data_ov078_020c5024[i - 1].stride;
    }
    cursor = 0;
    menu->bufferA = Msg_OpenContainerAndReadHeader(sOv078_UiMenuQuestP2_020c5168, 0xe, 0);
    menu->bufferB = Msg_OpenContainerAndReadHeader(sOv078_UiMenuLanguageQuestP2_020c517c, 0xe, 0);
    menu->bufferC = Msg_OpenContainerAndReadHeader(sOv078_UiBtlStrLanguageP2_020c5190, 0xe, 0);
    LoadPackedFileView(&menu->imageA, sOv078_UiMenuStrLanguageQstSZ_020c51a0, 0);
    LoadPackedFileView(&menu->imageB,
                                (const void *)(((((u32)menu->bufferC + 0x8000) & 0xfffffc) << 7) | 0x80000000), 0);
    AcquireRecordManager();
    AcquireRecordSlot(2, 0);
    AcquireRecordSlot(0, 0);
    func_ov078_020c43e0(menu);
    LoadPageMenuWidgets(menu);
    if ((s8)data_0205fe0c[0x28d4] < 5) {
        cursor = (s8)data_0205fe0c[0x28d4];
    }
    menu->cursor = cursor;
    InitSequence(menu);
    return TRUE;
}
