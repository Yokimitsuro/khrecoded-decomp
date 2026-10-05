#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[4];
    u16 width;
    u16 height;
    u8 pad_08[8];
    fx32 x;
    fx32 y;
    u8 pad_18[8];
    int frame;
    u8 visible;
    u8 pad_25;
    u8 alpha : 5;
    u8 pad_26_5 : 3;
    u8 pad_27[5];
} PopupEntry;

typedef struct {
    u8 pad_000[0x3ec];
    int popupRows[(0x414 - 0x3ec) / 4];
} EntryLayout;

typedef struct {
    int entryIndex;
    u8 pad_0004[0x14];
    int fileBase;
    u8 pad_001c[0xce08 - 0x1c];
    EntryLayout layouts[1];
    u8 pad_d21c[0xeea8 - 0xd21c];
    PopupEntry popups[10];
    int popupCount;
} MenuScene;

typedef struct {
    int popupIds[10];
    int popupCount;
    u8 pad_2c[8];
} EntryPopupTable;

extern EntryPopupTable data_ov097_020c2144[];
extern u32 data_ov097_020c1f3c[];
extern void NNS_GfdResetFrmTexVramState(void);
extern void NNS_GfdResetFrmPlttVramState(void);
extern BOOL func_ov097_020c1864(PopupEntry *slot, u32 fileId);

#define ROW_TO_FX32(row) ((fx32)((float)(row) > 0 ? 0.5f + 4096.0f * (float)(row) : 4096.0f * (float)(row) - 0.5f))

void CreateEntryPopups(MenuScene *scene)
{
    int entryIndex = scene->entryIndex;
    EntryPopupTable *table = &data_ov097_020c2144[entryIndex];
    EntryLayout *layout = &scene->layouts[entryIndex];
    int i;
    PopupEntry *popup;
    int row;

    NNS_GfdResetFrmTexVramState();
    NNS_GfdResetFrmPlttVramState();
    scene->popupCount = 0;
    for (i = 0; i < table->popupCount; i++) {
        popup = &scene->popups[i];
        func_ov097_020c1864(popup, ((scene->fileBase + 0x8000) & 0xfffffc) << 7 | 0x80000000 | (data_ov097_020c1f3c[table->popupIds[i]] & 0x1ff));
        popup->frame = 0;
        popup->visible = 1;
        popup->alpha = 0x1f;
        popup->width = 0x80;
        popup->height = 0x68;
        popup->x = 0x80000;
        row = layout->popupRows[i];
        popup->y = ROW_TO_FX32(row);
        scene->popupCount++;
    }
}
