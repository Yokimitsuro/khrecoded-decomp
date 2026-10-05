#include "nitro/types.h"

typedef struct StringTable {
    void *buffer;
    u32 count;
    u8 *entries;
} StringTable;

typedef struct StatusMenu {
    u8 pad_000[0x24];
    BOOL useAltTitle;
    u8 pad_028[0xe5c - 0x28];
    u16 shortText[2][0x20];
    u16 longText[2][0x70];
    u8 pad_109c[0x11cc - 0x109c];
    StringTable strings;
} StatusMenu;

extern const u16 data_ov073_020c41a0[];
extern u16 *func_ov027_020ba2c8(StringTable *table, int index);
extern int OS_SNPrintf_0202e094(u16 *dst, u32 length, const u16 *format, ...);

void ResetStatusHeaderText(StatusMenu *menu)
{
    u16 *title;
    int titleIndex = 0x29;

    if (!menu->useAltTitle) {
        titleIndex = 0;
    }
    title = func_ov027_020ba2c8(&menu->strings, titleIndex);
    menu->shortText[0][0] = 0;
    menu->shortText[1][0] = 0;
    OS_SNPrintf_0202e094(menu->longText[0], 0x70, data_ov073_020c41a0, title);
    OS_SNPrintf_0202e094(menu->longText[1], 0x70, data_ov073_020c41a0, title);
}
