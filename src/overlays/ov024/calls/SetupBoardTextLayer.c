#include "nitro/types.h"

typedef struct TextColors {
    u16 colors[8];
} TextColors;

typedef struct BoardState {
    char pad0000[8];
    void *widget;
    char pad000c[0x64fc - 0xc];
    int textReady;
    char layer[0x650c - 0x6500];
    char fontA[0xc];
    char fontB[0xc];
    char textLayer[0x66e0 - 0x6524];
    int useCustomFont;
} BoardState;

typedef struct BoardGlobals {
    BoardState *state;
    int unk04;
    void *widget;
} BoardGlobals;

extern TextColors data_ov024_020b7340;
extern BoardGlobals data_ov024_020b7540;
extern char sOv024_TextFontEu10Nftr_020b74b4[];
extern char sOv024_TextFontEu10sNftr_020b74cc[];
extern char sOv024_UiBtlStrLanguageP2_020b74e4[];

extern void *func_ov027_020b9e10(void *widget, int layer);
extern void func_ov027_020b9e20(void *widget, int layer);
extern void LoadPackedFileView(void *layer, u32 key, int value);
extern void func_0200146c(void *font, const char *path);
extern void InitTextLayerAtFromEnd(void *textLayer, int count, void *screen, void *font, TextColors *colors);
extern void *GetFieldFont3(void);
extern int Msg_OpenContainerAndReadHeader(const char *path, int heap, int flags);
extern void ZeroHalfThenFree(int handle);

void SetupBoardTextLayer(void)
{
    TextColors colors = data_ov024_020b7340;
    void *widget = data_ov024_020b7540.state->widget;
    void *screen = func_ov027_020b9e10(widget, 0x18);
    int handle;

    if (data_ov024_020b7540.state->useCustomFont) {
        func_0200146c(data_ov024_020b7540.state->fontA, sOv024_TextFontEu10Nftr_020b74b4);
        InitTextLayerAtFromEnd(data_ov024_020b7540.state->textLayer, 4, screen, data_ov024_020b7540.state->fontA, &colors);
        func_0200146c(data_ov024_020b7540.state->fontB, sOv024_TextFontEu10sNftr_020b74cc);
    } else {
        InitTextLayerAtFromEnd(data_ov024_020b7540.state->textLayer, 4, screen, GetFieldFont3(), &colors);
    }
    func_ov027_020b9e20(widget, 0x18);
    handle = Msg_OpenContainerAndReadHeader(sOv024_UiBtlStrLanguageP2_020b74e4, 0xe, 0);
    LoadPackedFileView(data_ov024_020b7540.state->layer, ((handle + 0x8000) & 0xfffffc) << 7 | 0x80000007, 1);
    ZeroHalfThenFree(handle);
    data_ov024_020b7540.state->textReady = 1;
}
