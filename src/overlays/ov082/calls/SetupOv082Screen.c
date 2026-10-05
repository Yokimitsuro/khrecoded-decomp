#include "nitro/types.h"

#define ARCHIVE_FILE_ID(handle, index) ((((u32)(handle) + 0x8000) & 0xfffffc) << 7 | 0x80000000 | (index))

typedef struct ScreenData {
    u8 pad_00[0x8];
    u32 size;
    u8 rawData[1];
} ScreenData;

typedef struct CharacterData {
    u8 pad_00[0x10];
    u32 size;
    void *rawData;
} CharacterData;

typedef struct PaletteData {
    u8 pad_00[0x8];
    u32 size;
    void *rawData;
} PaletteData;

typedef struct BgGraphicsData {
    ScreenData *screen;
    CharacterData *character;
    PaletteData *palette;
} BgGraphicsData;

typedef struct WindowStyle {
    u16 unk_00[4];
    u16 fillColor;
    u16 unk_0A[3];
} WindowStyle;

typedef struct TextWindow {
    u8 data[0x34];
} TextWindow;

typedef struct Ov081State {
    u32 archive;
    u32 subArchive;
} Ov081State;

typedef struct Ov082State {
    u8 list[0x28];
    u8 pad_0028[0xd4 - 0x28];
    u8 rowTiles[9][0x600];
    TextWindow window;
    int needsRedraw;
    void *entryFile;
    void *headerFile;
    BgGraphicsData entryBg;
    BgGraphicsData headerBg;
} Ov082State;

extern void *data_0205fe0c;
extern const WindowStyle data_ov082_020bf674;

extern Ov081State *func_ov081_020c5bf8(void);
extern void GXS_SetGraphicsMode(int value);
extern void G2x_SetBlendAlpha_(vu32 *reg, int plane1, int plane2, int ev1, int ev2);
extern void *G2S_GetBG1ScrPtr(void);
extern void *G2S_GetBG2ScrPtr(void);
extern void *G2S_GetBG3ScrPtr(void);
extern void MIi_CpuClearFast(u32 value, void *dst, u32 size);
extern void *func_0202c4a0(u32 fileId, int heapId);
extern void GetBgDataFromArchive(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                          int paletteIndex);
extern void GXS_LoadBGPltt(const void *src, u32 offset, u32 size);
extern void GXS_LoadBG2Char(const void *src, u32 offset, u32 size);
extern void GXS_LoadBG3Scr(const void *src, u32 offset, u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void DrawEntryRowFrames(Ov082State *state);
extern void OpenTextFrame(int position, int size, int palette, TextWindow *window, WindowStyle *style);
extern u16 *func_ov039_020bcb40(void *save);
extern void SetTextColorIfFits(TextWindow *window, int messageId, u16 *text);
extern void DrawTextAnchored(TextWindow *window, int x, int y, int color, u32 flags, const u16 *text);
extern void Text_UploadTileBuffer(TextWindow *window);
extern void func_ov082_020bf468(Ov082State *state);
extern void RefreshEntryRows(Ov082State *state);

static inline void SetWindowOutsidePlane(int planeMask, BOOL effect)
{
    u32 value = (*(vu16 *)0x0400104a & ~0x3f) | planeMask;
    if (effect) {
        value |= 0x20;
    }
    *(vu16 *)0x0400104a = (u16)value;
}

static inline void SetWindow0InsidePlane(int planeMask, BOOL effect)
{
    u32 value = (*(vu16 *)0x04001048 & ~0x3f) | planeMask;
    if (effect) {
        value |= 0x20;
    }
    *(vu16 *)0x04001048 = (u16)value;
}

static inline void SetWindow1InsidePlane(int planeMask, BOOL effect)
{
    u32 value = (*(vu16 *)0x04001048 & ~0x3f00) | (planeMask << 8);
    if (effect) {
        value |= 0x2000;
    }
    *(vu16 *)0x04001048 = (u16)value;
}

void SetupOv082Screen(Ov082State *state)
{
    Ov081State *source = func_ov081_020c5bf8();
    BgGraphicsData bg;
    WindowStyle style;
    void *archive;
    u16 *title;

    GXS_SetGraphicsMode(0);
    G2x_SetBlendAlpha_((vu32 *)0x04001050, 1, 0x1e, 16, 16);
    *(vu32 *)0x04001000 = (*(vu32 *)0x04001000 & ~0x1f00) | 0x1f00;
    *(vu16 *)0x04001008 = (u16)((*(vu16 *)0x04001008 & ~3) | 0);
    *(vu16 *)0x0400100a = (u16)((*(vu16 *)0x0400100a & ~3) | 1);
    *(vu16 *)0x0400100c = (u16)((*(vu16 *)0x0400100c & ~3) | 2);
    *(vu16 *)0x0400100e = (u16)((*(vu16 *)0x0400100e & ~3) | 3);
    *(vu32 *)0x04001010 = 0;
    *(vu32 *)0x04001014 = 0x1fe0000;
    *(vu32 *)0x04001018 = 0;
    *(vu32 *)0x0400101c = 0;
    SetWindowOutsidePlane(0x1f, TRUE);
    SetWindow0InsidePlane(0x1f, TRUE);
    SetWindow1InsidePlane(0x1f, TRUE);
    *(vu32 *)0x04001000 = (*(vu32 *)0x04001000 & ~0xe000) | 0x6000;
    *(vu16 *)0x04001008 = (u16)((*(vu16 *)0x04001008 & 0x43) | 0xa00);
    *(vu16 *)0x0400100a = (u16)((*(vu16 *)0x0400100a & 0x43) | 0xb00);
    *(vu16 *)0x0400100c = (u16)((*(vu16 *)0x0400100c & 0x43) | 0xd00);
    *(vu16 *)0x0400100e = (u16)((*(vu16 *)0x0400100e & 0x43) | 0xf00);

    MIi_CpuClearFast(0, G2S_GetBG1ScrPtr(), 0x600);
    MIi_CpuClearFast(0, G2S_GetBG2ScrPtr(), 0x600);
    MIi_CpuClearFast(0, G2S_GetBG3ScrPtr(), 0x600);

    state->entryFile = func_0202c4a0(ARCHIVE_FILE_ID(source->archive, 1), 0xf);
    state->headerFile = func_0202c4a0(ARCHIVE_FILE_ID(source->archive, 1), 0xf);
    GetBgDataFromArchive(&state->entryBg, state->entryFile, 1, 0, 0);
    GetBgDataFromArchive(&state->headerBg, state->headerFile, 2, 0, 0);
    GXS_LoadBGPltt(state->entryBg.palette->rawData, 0, state->entryBg.palette->size);
    GXS_LoadBG2Char(state->entryBg.character->rawData, 0, state->entryBg.character->size);
    DrawEntryRowFrames(state);

    archive = func_0202c4a0(ARCHIVE_FILE_ID(source->archive, 1), 0xf);
    GetBgDataFromArchive(&bg, archive, 0, 0, 0);
    GXS_LoadBG3Scr(bg.screen->rawData, 0, bg.screen->size);
    NNSi_FndFreeFromDefaultHeap(archive);

    archive = func_0202c4a0(ARCHIVE_FILE_ID(source->subArchive, 1), 0xf);
    GetBgDataFromArchive(&bg, archive, 0, 0, 0);
    GXS_LoadBG2Char(bg.character->rawData, 0x1000, bg.character->size);
    NNSi_FndFreeFromDefaultHeap(archive);

    MIi_CpuClearFast(0, state->rowTiles, sizeof(state->rowTiles));
    style = data_ov082_020bf674;
    OpenTextFrame(8, 0x20018, 4, &state->window, &style);
    title = func_ov039_020bcb40(data_0205fe0c);
    SetTextColorIfFits(&state->window, 0xac, title);
    DrawTextAnchored(&state->window, 0xbe, 2, 2, 0x20, title);
    Text_UploadTileBuffer(&state->window);
    func_ov082_020bf468(state);
    RefreshEntryRows(state);
}
