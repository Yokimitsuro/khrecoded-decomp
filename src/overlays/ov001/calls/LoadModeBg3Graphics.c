#include "nitro/types.h"

typedef struct {
    u32 fmt;
    BOOL extended;
    u32 szByte;
    void *pRawData;
} PaletteData;

typedef struct {
    u32 pixelFmt;
    u32 mapingType;
    u32 characterFmt;
    u32 unk_0C;
    u32 szByte;
    void *pRawData;
} CharacterData;

typedef struct {
    void *screen;
    CharacterData *character;
    PaletteData *palette;
} BgGraphicsData;

typedef struct {
    u32 active;
    u8 modeState[8];
    s32 mode;
    s32 layout;
    u8 pad_14[0xe4];
    BOOL skipLoad;
} ActiveContext;

extern ActiveContext *data_ov001_020a04e4;

extern void *func_ov027_020ba1f8(void *resource);
extern void func_ov027_020ba200(void *resource, BOOL freeData);
extern void GetBgDataFromArchive(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                          int paletteIndex);
extern void GX_LoadBGPltt(void *src, u32 offset, u32 size);
extern void GX_LoadBG3Char(const void *src, u32 offset, u32 size);
extern void func_ov001_0207a1d0(void *modeState, s32 layout);
extern void LoadMenuEntryPanel(void *modeState, s32 layout);

void LoadModeBg3Graphics(void *resource, u32 active)
{
    BgGraphicsData graphics;
    ActiveContext *context;

    if (data_ov001_020a04e4->skipLoad) {
        func_ov027_020ba200(resource, TRUE);
        return;
    }
    data_ov001_020a04e4->active = active;
    GetBgDataFromArchive(&graphics, func_ov027_020ba1f8(resource), -1, 0, 0);
    GX_LoadBGPltt(graphics.palette->pRawData, 0, graphics.palette->szByte);
    GX_LoadBG3Char(graphics.character->pRawData, 0, graphics.character->szByte);
    func_ov027_020ba200(resource, TRUE);
    context = data_ov001_020a04e4;
    if (context->mode == 1) {
        if (context->layout == 0) {
            func_ov001_0207a1d0(context->modeState, context->layout);
        } else {
            LoadMenuEntryPanel(context->modeState, context->layout);
        }
    }
}
