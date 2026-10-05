#include "nitro/types.h"

#define REG_DB_DISPCNT (*(vu32 *)0x04001000)
#define REG_DB_BG0CNT (*(vu16 *)0x04001008)
#define REG_DB_BG1CNT (*(vu16 *)0x0400100a)
#define REG_DB_BG2CNT (*(vu16 *)0x0400100c)
#define REG_DB_BG3CNT (*(vu16 *)0x0400100e)

typedef struct CharResource {
    u8 pad_00[0x10];
    u32 size;
    void *data;
} CharResource;

typedef struct PaletteResource {
    u8 pad_00[0xc];
    u8 *data;
} PaletteResource;

typedef struct StatusPanel {
    u8 pad_000[0x148];
    u8 uploads[0x15c - 0x148];
    BOOL uploadImmediate;
    u8 pad_160[0x168 - 0x160];
    BOOL needsRedraw;
    u8 pad_16c[0x174 - 0x16c];
    BOOL restoreLayers;
    u8 pad_178[0x180 - 0x178];
    CharResource *bgChar;
    u8 pad_184[0x194 - 0x184];
    PaletteResource *bgPalette;
    u8 titleLayer[0x1cc - 0x198];
    u8 textLayer[1];
} StatusPanel;

extern StatusPanel *data_ov073_020c4260;

extern void GXS_LoadBGPltt(const void *src, u32 offset, u32 size);
extern void GXS_LoadBG3Char(const void *src, u32 offset, u32 size);
extern void *UpdateScreenWidgetLayer(int widget);
extern void GXS_LoadBG0Scr(const void *src, u32 offset, u32 size);
extern void GXS_LoadBG1Scr(const void *src, u32 offset, u32 size);
extern void func_ov027_020b9e20(void *table, int id);
extern void FlushDirtyTileTableRows(void *uploads);
extern void FlushBufferAndRunCallback(void *context);

int RestoreStatusSubScreen(void)
{
    REG_DB_BG0CNT = (REG_DB_BG0CNT & 0x43) | 0x0a00;
    REG_DB_BG1CNT = (REG_DB_BG1CNT & 0x43) | 0x0b04;
    REG_DB_BG2CNT = (REG_DB_BG2CNT & 0x43) | 0x4c00;
    REG_DB_BG3CNT = (REG_DB_BG3CNT & 0x43) | 0x4e04;
    GXS_LoadBGPltt(data_ov073_020c4260->bgPalette->data, 0, 0xa0);
    GXS_LoadBGPltt(data_ov073_020c4260->bgPalette->data + 0x100, 0x100, 0x100);
    GXS_LoadBG3Char(data_ov073_020c4260->bgChar->data, 0, data_ov073_020c4260->bgChar->size);
    GXS_LoadBG0Scr(UpdateScreenWidgetLayer(0x18), 0, 0x800);
    GXS_LoadBG1Scr(UpdateScreenWidgetLayer(0x19), 0, 0x800);
    func_ov027_020b9e20(data_ov073_020c4260->uploads, 0x1a);
    func_ov027_020b9e20(data_ov073_020c4260->uploads, 0x1b);
    data_ov073_020c4260->uploadImmediate = TRUE;
    FlushDirtyTileTableRows(data_ov073_020c4260->uploads);
    data_ov073_020c4260->uploadImmediate = FALSE;
    FlushBufferAndRunCallback(data_ov073_020c4260->textLayer);
    FlushBufferAndRunCallback(data_ov073_020c4260->titleLayer);
    REG_DB_DISPCNT = (REG_DB_DISPCNT & ~0x1f00) | 0x1f00;
    data_ov073_020c4260->restoreLayers = TRUE;
    data_ov073_020c4260->needsRedraw = TRUE;
    return 0;
}
