#include "nitro/types.h"

typedef struct RecordEntry {
    u8 pad_00[0x2c];
    const u16 *name;
} RecordEntry;

typedef struct StatusPanel {
    u8 pad_000[0x1cc];
    u8 textLayer[0x200 - 0x1cc];
    int selectedRecord;
} StatusPanel;

typedef struct StatusMenu {
    s8 mode;
    u8 pad_01[3];
    u16 digitBase;
    u16 numberBase;
    u8 pad_08[0xb44 - 0x08];
    StatusPanel panel;
    u8 pad_d48[0x10dc - 0xd48];
    void *recordPool;
    void *container;
    u8 pad_10e4[0x11cc - 0x10e4];
    u8 strings[1];
} StatusMenu;

extern int func_ov073_020c3fc4(StatusPanel *panel);
extern void SetStatusElementVisible(int elementId, BOOL visible);
extern void CallVirtualHandlerSlot1(void *context, int arg);
extern u16 *func_ov027_020ba2c8(void *table, int index);
extern void *func_ov039_020bc9cc(void);
extern void *func_ov039_020bc9b4(void);
extern void func_02001620(void *layer, int x, int y, int color, u32 flags, const u16 *text, void *fallbackFont, int maxWidth);
extern RecordEntry *GetRecordSlotPair1Entry(int index);
extern int func_0200191c(void *layer, const u16 *text, const u16 **next);
extern void Obj_SetField14(void *layer, void *font);
extern void DrawTextColored(void *layer, int x, int y, int color, int altColor, const u16 *text);
extern void FlushBufferAndRunCallback(void *context);
extern void *FindActiveRecordById(void *pool, u32 recordId);
extern void func_ov027_020b8230(void *pool, void *record);
extern void SetDigitDisplay(void *cells, int first, int value, void *origin);
extern void func_ov039_020be470(void *cells, int first, int value, void *origin);

void ShowSelectedRecordName(StatusMenu *menu)
{
    StatusPanel *panel;
    int maxWidth = 0;
    int recordIndex;
    const u16 *text;
    int width;

    if (menu->mode == 4) {
        panel = &menu->panel;
        recordIndex = func_ov073_020c3fc4(panel);
        SetStatusElementVisible(0xe, TRUE);
        CallVirtualHandlerSlot1(panel->textLayer, 0);
        if (recordIndex == -1) {
            func_02001620(panel->textLayer, 4, 0, 2, 0x209, func_ov027_020ba2c8(menu->strings, 0x24),
                          func_ov039_020bc9cc(), 0xe4);
        } else {
            text = GetRecordSlotPair1Entry(recordIndex)->name;
            do {
                width = func_0200191c(panel->textLayer, text, &text);
                if (maxWidth < width) {
                    maxWidth = width;
                }
            } while (text != NULL);
            if (maxWidth > 0xe4) {
                Obj_SetField14(panel->textLayer, func_ov039_020bc9cc());
            }
            DrawTextColored(panel->textLayer, 4, 0, 2, 10, GetRecordSlotPair1Entry(recordIndex)->name);
            Obj_SetField14(panel->textLayer, func_ov039_020bc9b4());
        }
        FlushBufferAndRunCallback(panel->textLayer);
        panel->selectedRecord = recordIndex;
        return;
    }
    func_ov027_020b8230(menu->recordPool, FindActiveRecordById(menu->recordPool, 10));
    SetStatusElementVisible(6, FALSE);
    SetStatusElementVisible(7, FALSE);
    SetDigitDisplay(menu->container, menu->digitBase, -1, NULL);
    func_ov039_020be470(menu->container, menu->numberBase, -1, NULL);
}
