#include "nitro/types.h"

typedef struct SaveData {
    u8 pad_0000[0x28d0];
    int munny;
} SaveData;

typedef struct StatusPanel {
    u8 pad_000[0x1cc];
    u8 textLayer[0x10dc - 0xd10];
} StatusPanel;

typedef struct StatusMenu {
    s8 mode;
    u8 pad_01;
    u8 refreshCount;
    u8 pad_03;
    u16 digitBase;
    u16 numberBase;
    u8 pad_08[4];
    int numberValue;
    u8 pad_10[0xb44 - 0x10];
    StatusPanel panel;
    void *recordPool;
    void *container;
    u8 pad_10e4[0x11cc - 0x10e4];
    u8 strings[1];
} StatusMenu;

extern SaveData *data_0205fe0c;

extern void SetStatusElementVisible(int elementId, BOOL visible);
extern void CallVirtualHandlerSlot1(void *context, int arg);
extern u16 *func_ov027_020ba2c8(void *table, int index);
extern void DrawTextAnchored(void *layer, int x, int y, int color, u32 flags, const u16 *text);
extern void FlushBufferAndRunCallback(void *context);
extern void func_ov039_020bc934(void);
extern void *FindActiveRecordById(void *pool, u32 recordId);
extern void func_ov027_020b8288(void *pool, void *record);
extern void SetDigitDisplay(void *cells, int first, int value, void *origin);
extern void func_ov039_020be470(void *cells, int first, int value, void *origin);
extern void ResetStatusHeaderText(StatusMenu *menu);

void ShowStatusPageContents(StatusMenu *menu)
{
    if (menu->mode == 4) {
        StatusPanel *panel = &menu->panel;

        SetStatusElementVisible(0xe, FALSE);
        CallVirtualHandlerSlot1(panel->textLayer, 0);
        DrawTextAnchored(panel->textLayer, 4, 0, 2, 8, func_ov027_020ba2c8(menu->strings, 0));
        FlushBufferAndRunCallback(panel->textLayer);
        return;
    }
    func_ov039_020bc934();
    func_ov027_020b8288(menu->recordPool, FindActiveRecordById(menu->recordPool, 10));
    SetStatusElementVisible(6, TRUE);
    SetStatusElementVisible(7, TRUE);
    SetDigitDisplay(menu->container, menu->digitBase, data_0205fe0c->munny, NULL);
    func_ov039_020be470(menu->container, menu->numberBase, menu->numberValue, NULL);
    ResetStatusHeaderText(menu);
    menu->refreshCount++;
}
