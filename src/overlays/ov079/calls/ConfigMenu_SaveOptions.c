#include "nitro/types.h"

typedef struct ConfigOption {
    u8 count;
    u8 value;
    u16 bitWidth : 2;
    u16 locked : 1;
    u16 bitIndex : 13;
} ConfigOption;

typedef struct ConfigPage {
    u8 rowCount;
    u8 pad_01[7];
    ConfigOption *options[6];
} ConfigPage;

typedef struct RowLayout {
    u8 pad_00[2];
    s16 x;
    s16 y;
} RowLayout;

typedef struct ConfigMenu {
    u8 row;
    u8 page;
    u8 pad_02;
    u8 dirty;
    u8 pageChanged;
    u8 pad_05[3];
    void *tracker;
    void *rowTags[6];
    void *cursorTag;
    u8 pad_28[4];
    void *headerTag;
    void *pageTabs[3];
    void *footerTag;
    void *arrowLeft;
    void *arrowRight;
    u8 pad_48[8];
    ConfigPage pages[3];
    u8 objectLists[5][0x34];
    void *image;
} ConfigMenu;

extern u8 *data_0205fe0c;
extern void WritePackedBits(u32 *base, u32 bitOffset, u32 bitCount, u32 value);

void ConfigMenu_SaveOptions(ConfigMenu *menu)
{
    u16 page;
    u16 row;

    for (page = 0; page < 3; page++) {
        for (row = 0; row < menu->pages[page].rowCount; row++) {
            ConfigOption *option = menu->pages[page].options[row];
            if (!option->locked) {
                int width = option->bitWidth;
                int index = option->bitIndex;
                WritePackedBits((u32 *)(data_0205fe0c + 0x2878), (index / 32) * 32 + 32 - (index + width),
                                         width, option->value);
            }
        }
    }
}
