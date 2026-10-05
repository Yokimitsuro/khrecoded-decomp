#include "nitro/types.h"

typedef struct {
    u8 pad_0[8];
    int textId;
} Ov089Entry;

typedef struct {
    u8 pad_000[0x738];
    Ov089Entry *entries;
    u8 pad_73C[0xc];
    int cursor;
    u8 pad_74C[0x38];
    u8 captionLayer[0x16c];
    u8 messages[4];
} Ov089Menu;

extern void CallVirtualHandlerSlot1(void *layer, int arg);
extern int GetGridTableValue(int row, int column);
extern void *func_ov027_020ba2c8(void *messages, int index);
extern void DrawTextAnchored(void *layer, int x, int y, int color, u32 flags, const u16 *text);
extern void Text_UploadTileBuffer(void *layer);
extern BOOL PlaySoundEffect(int seqArcNo, int index);

void RefreshEntryCaption(Ov089Menu *menu, BOOL playSound)
{
    int textId = menu->entries[menu->cursor].textId;
    const u16 *text;

    CallVirtualHandlerSlot1(menu->captionLayer, 0);
    if (textId >= 0) {
        text = (const u16 *)GetGridTableValue(textId, -1);
    } else {
        text = func_ov027_020ba2c8(menu->messages, 4);
    }
    DrawTextAnchored(menu->captionLayer, 0x40, 2, 2, 0x411, text);
    Text_UploadTileBuffer(menu->captionLayer);
    if (playSound) {
        PlaySoundEffect(0, 0);
    }
}
