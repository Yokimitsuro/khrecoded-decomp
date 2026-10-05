#include "nitro/types.h"

typedef struct {
    void *buffer;
    u8 pad_04[8];
} GlyphBuffer;

typedef struct {
    u16 *lines[0x3e8 / 4];
    int lineCount;
    int popupRows[(0x414 - 0x3ec) / 4];
} EntryLayout;

typedef struct {
    int handle;
    int visibleRows;
    int totalRows;
    int slots[8];
} ScrollListDesc;

typedef struct {
    char text[9];
} PopupTag;

typedef struct {
    int selectedEntry;
    BOOL unk_04;
    u8 pad_0008[0xcde4 - 0x8];
    GlyphBuffer glyphBuffers[3];
    EntryLayout layouts[8];
    u8 pad_eea8[0xf06c - 0xeea8];
    int unk_f06c;
    int unk_f070;
    int unk_f074;
    int unk_f078;
    int unk_f07c;
    int unk_f080;
    u8 pad_f084[0xf0cc - 0xf084];
    int entryCount;
} MenuScene;

extern MenuScene *data_ov097_020c2540;
extern PopupTag data_ov097_020c1dcc;
extern ScrollListDesc data_ov097_020c1ee4;
extern ScrollListDesc data_ov097_020c1f10;
extern void SetStateFlagBits(u8 clearMask, u8 setBits);
extern void MIi_CpuClearFast(u32 data, void *dest, u32 size);
extern void MIi_CpuCopyFast(const void *src, void *dest, u32 size);
extern void SyncUnlockedEntryFlags(MenuScene *scene);
extern void func_ov097_020bf46c(MenuScene *scene);
extern void func_ov097_020bf6c8(MenuScene *scene);
extern void LoadMenuGraphics_020bf734(MenuScene *scene);
extern void func_ov097_020bf95c(MenuScene *scene);
extern void InitMenuPanels(MenuScene *scene);
extern void ApplyTouchRegionBounds(MenuScene *scene);
extern void ResetScrollTrack(int trackIndex);
extern void *func_ov027_020ba2c8(GlyphBuffer *view, int index);
extern int CompareByteStrings(void *leftBytes, void *rightBytes, int length);
extern void CreateEntryPopups(MenuScene *scene);
extern void func_ov097_020c0314(ScrollListDesc *desc, MenuScene *scene);
extern void func_ov097_020bfb58(int listIndex, MenuScene *scene);
extern void func_ov097_020c1578(int value, MenuScene *scene);

BOOL InitMenuScene_020beb20(MenuScene *scene)
{
    PopupTag tag;
    ScrollListDesc desc;
    int i;
    u16 *text;
    GlyphBuffer *descriptions;
    EntryLayout *layout;
    int popupCount;

    data_ov097_020c2540 = scene;
    SetStateFlagBits(5, 0);
    MIi_CpuClearFast(0, scene, 0xf0d0);
    scene->selectedEntry = 0;
    scene->unk_04 = 0;
    scene->unk_f078 = 0;
    scene->unk_f07c = 0;
    scene->unk_f080 = 0;
    scene->entryCount = 1;
    scene->unk_f06c = 0;
    scene->unk_f074 = 0;
    scene->unk_f070 = 0;
    SyncUnlockedEntryFlags(scene);
    func_ov097_020bf46c(scene);
    func_ov097_020bf6c8(scene);
    LoadMenuGraphics_020bf734(scene);
    func_ov097_020bf95c(scene);
    InitMenuPanels(scene);
    ApplyTouchRegionBounds(scene);
    ResetScrollTrack(0);
    descriptions = &scene->glyphBuffers[2];
    tag = data_ov097_020c1dcc;
    for (i = 0; i < 8; i++) {
        layout = &scene->layouts[i];
        popupCount = 0;
        text = func_ov027_020ba2c8(descriptions, i);
        layout->lineCount = 0;
        layout->lines[layout->lineCount] = text;
        while (*text != 0) {
            if (*text == '\n') {
                *text++ = 0;
                layout->lineCount++;
                layout->lines[layout->lineCount] = text;
            } else if (CompareByteStrings(text, &tag, 8) == 0) {
                layout->popupRows[popupCount] = layout->lineCount * 16 + 0x58;
                text[3] = 0;
                layout->lines[layout->lineCount] = text + 3;
                popupCount++;
                layout->lineCount++;
                layout->lines[layout->lineCount] = text + 3;
                layout->lineCount++;
                layout->lines[layout->lineCount] = text + 3;
                layout->lineCount++;
                layout->lines[layout->lineCount] = text + 3;
                layout->lineCount++;
                layout->lines[layout->lineCount] = text + 3;
                layout->lineCount++;
                layout->lines[layout->lineCount] = text + 3;
                layout->lineCount++;
                layout->lines[layout->lineCount] = text + 3;
                text += 4;
            } else {
                text++;
            }
        }
        layout->lineCount++;
    }
    CreateEntryPopups(scene);
    MIi_CpuCopyFast(&data_ov097_020c1ee4, &desc, sizeof(desc));
    desc.visibleRows = desc.totalRows = scene->entryCount;
    func_ov097_020c0314(&desc, scene);
    data_ov097_020c1f10.totalRows = scene->layouts[scene->selectedEntry].lineCount;
    func_ov097_020c0314(&data_ov097_020c1f10, scene);
    func_ov097_020bfb58(-1, scene);
    func_ov097_020c1578(1, scene);
    return TRUE;
}
