#include "nitro/types.h"

typedef struct {
    int ids[5];
} TextIdTable;

typedef struct {
    u8 textId;
    u8 pad_01[3];
} RankTextEntry;

typedef struct {
    u8 pad_0000[0x3a];
    char playerName[0x51 - 0x3a];
    s8 partnerRank;
    s8 resultKind;
    s8 playerRank;
    s8 titleIndex;
    u8 pad_0055[3];
    s8 score;
    u8 pad_0059[0x65e0 - 0x59];
    int textBank[3];
    void *headerText;
    void *bodyText;
} PanelWork;

extern PanelWork *data_ov015_020812e0;
extern const TextIdTable data_ov015_0207a2b8;
extern const TextIdTable data_ov015_0207a2cc;
extern RankTextEntry data_ov015_0207a40f[];
extern void *NNS_FndAllocFromDefaultExpHeapEx(u32 size, int align);
extern void MI_CpuFill8(void *dest, u8 data, u32 size);
extern void func_ov015_0207533c(int a, int b, int c);
extern void func_ov015_020759cc(void);
extern void *func_ov027_020ba2c8(int *bank, int index);
extern void func_ov015_02075034(u16 *dst, const void *first, const void *second, int value);
extern void DrawCenteredLayerText(void *object, int x, int y, int color, int width, const void *text);
extern void Text_UploadTileBuffer(void *surface);
extern void *SPrintfUnbounded(void *dst, const void *fmt, ...);
extern int MeasureTextWidth(void *font, const u16 *text, int maxLines);
extern void func_ov015_02079d6c(void);

void SetupResultPanel(int a, int b, int c) {
    TextIdTable titleIds;
    TextIdTable altIds;
    u16 headerBuf[0x100];
    u16 bodyBuf[0x100];
    PanelWork *work;
    void *title;
    s8 kind;

    data_ov015_020812e0 = NNS_FndAllocFromDefaultExpHeapEx(0x20138, 4);
    MI_CpuFill8(data_ov015_020812e0, 0, 0x20138);
    func_ov015_0207533c(a, b, c);
    func_ov015_020759cc();
    work = data_ov015_020812e0;
    titleIds = data_ov015_0207a2b8;
    title = func_ov027_020ba2c8(work->textBank, titleIds.ids[work->titleIndex]);
    func_ov015_02075034(headerBuf, title, func_ov027_020ba2c8(work->textBank, data_ov015_0207a40f[work->playerRank].textId), work->score);
    DrawCenteredLayerText(data_ov015_020812e0->headerText, 0, 0, 0xf, 0, headerBuf);
    Text_UploadTileBuffer(data_ov015_020812e0->headerText);
    work = data_ov015_020812e0;
    kind = work->resultKind;
    if (kind != 0) {
        if (kind == 5) {
            SPrintfUnbounded(bodyBuf, func_ov027_020ba2c8(work->textBank, 1), work->playerName);
            if (MeasureTextWidth(data_ov015_020812e0->bodyText, bodyBuf, 0) > 100) {
                work = data_ov015_020812e0;
                SPrintfUnbounded(bodyBuf, func_ov027_020ba2c8(work->textBank, 2), work->playerName);
            }
            DrawCenteredLayerText(data_ov015_020812e0->bodyText, 0, 0, 0xf, 0, bodyBuf);
        } else if (kind == 6) {
            altIds = data_ov015_0207a2cc;
            title = func_ov027_020ba2c8(work->textBank, altIds.ids[work->titleIndex]);
            func_ov015_02075034(bodyBuf, title, func_ov027_020ba2c8(work->textBank, data_ov015_0207a40f[work->partnerRank].textId), 1);
            DrawCenteredLayerText(data_ov015_020812e0->bodyText, 0, 0, 0xf, 0, bodyBuf);
        }
        Text_UploadTileBuffer(data_ov015_020812e0->bodyText);
    }
    func_ov015_02079d6c();
}
