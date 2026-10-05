#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x10];
    int bgId;
} SlotFrame;

typedef struct {
    s32 status : 8;
    u32 statusHigh : 24;
    u8 pad_04[2];
    s16 emptyElement;
    s16 filledElement;
    u8 pad_0A[2];
    void *cursorElement;
    SlotFrame *frames[5];
    u8 pad_24[0x3830 - 0x24];
} SaveSlot;

typedef struct {
    u8 bytes[0x34];
} TextLayer;

typedef struct {
    u8 pad_00[0x54];
    void *panel;
    u8 pad_58[0x20];
    SaveSlot slots[2];
    u8 pad_70D8[0x37d4];
    TextLayer textLayer;
    u8 pad_A8E0[0x34];
    void *messages;
} SaveSelectScreen;

extern void CallStateWidget(int bgId, int x, int y, int width, int height);
extern void IndexedRecords_SetFlag2(void *panel, int index, BOOL visible);
extern void SetEntrySlotsVisible(void *panel, void *element, BOOL visible);
extern const u16 *func_ov027_020ba2c8(void **messages, int id);
extern void func_ov039_020be594(TextLayer *layer, int x, int y, int color, const u16 *text);
extern void DrawTextAnchored(TextLayer *layer, int x, int y, int color, u32 flags, const u16 *text);

void HideSaveSlotsShowPrompt(SaveSelectScreen *screen)
{
    void *panel = screen->panel;
    SaveSlot *slots = screen->slots;
    TextLayer *layer = &screen->textLayer;

    CallStateWidget(slots[0].frames[0]->bgId, 3, 7, 0x1b, 10);
    IndexedRecords_SetFlag2(panel, slots[0].emptyElement, FALSE);
    IndexedRecords_SetFlag2(panel, slots[0].filledElement, FALSE);
    SetEntrySlotsVisible(screen->panel, slots[0].cursorElement, FALSE);
    IndexedRecords_SetFlag2(panel, slots[1].emptyElement, FALSE);
    IndexedRecords_SetFlag2(panel, slots[1].filledElement, FALSE);
    SetEntrySlotsVisible(screen->panel, slots[1].cursorElement, FALSE);
    func_ov039_020be594(layer, 0x68, 0x18, 2, func_ov027_020ba2c8(&screen->messages, 0x15));
    DrawTextAnchored(layer, 0x34, 0x2b, 2, 0x10, func_ov027_020ba2c8(&screen->messages, 0xb));
    DrawTextAnchored(layer, 0x9c, 0x2b, 2, 0x10, func_ov027_020ba2c8(&screen->messages, 0xc));
}
