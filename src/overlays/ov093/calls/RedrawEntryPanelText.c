#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x34];
} TextLayer;

typedef struct {
    u8 pad_00[0xc];
} PackedFileView;

typedef struct {
    u8 pad_00[0x2c];
    int scrollPos;
    u8 pad_30[0x1c];
} ScrollBar;

typedef struct {
    u8 pad_00[4];
    int kind;
} ListItemInfo;

typedef struct {
    int nameIndex;
    ListItemInfo *info;
    int value;
} ListEntry;

typedef struct {
    u8 pad_0000[0x18];
    TextLayer textLayers[6];
    u8 pad_0150[0xcf1c - 0x150];
    PackedFileView views[4];
    int selectedIndex;
    u8 pad_cf50[4];
    ScrollBar bars[2];
    ListEntry entries[1];
} SceneWork;

extern char data_ov093_020c4d78[];
extern char data_ov093_020c4d80[];
extern char data_ov093_020c4d88[];

extern void *func_ov027_020ba2c8(PackedFileView *view, int index);
extern void CallVirtualHandlerSlot1(TextLayer *layer, int arg);
extern void Text_UploadTileBuffer(TextLayer *layer);
extern int GetNestedModeByte(TextLayer *layer);
extern void DrawShadowedAnchoredText_020c0060(TextLayer *layer, int x, int y, int color, u32 anchor, void *text);
extern void func_ov093_020c00c4(TextLayer *layer, int x, int y, int color, u32 flags, void *text);
extern BOOL IsEntryFlagSet_020c22c4(int flagSet, int entryIndex);
extern void *OS_SNPrintf_0202e094(char *dst, unsigned int len, const char *fmt, ...);

void RedrawEntryPanelText(int mode, SceneWork *work)
{
    char text[0x100];
    PackedFileView *titleView;
    ListEntry *entry;
    ScrollBar *bar;
    PackedFileView *nameView;
    int rowY;
    void *label;
    void *detail;
    int lineHeight;
    int selected;
    int i;

    titleView = &work->views[0];
    if (mode == 0 || mode == -1) {
        label = func_ov027_020ba2c8(titleView, 0);
        CallVirtualHandlerSlot1(&work->textLayers[0], 0);
        DrawShadowedAnchoredText_020c0060(&work->textLayers[0], 4, 2, 3, 0, label);
        Text_UploadTileBuffer(&work->textLayers[0]);
        label = func_ov027_020ba2c8(&work->views[1], work->selectedIndex);
        CallVirtualHandlerSlot1(&work->textLayers[1], 0);
        DrawShadowedAnchoredText_020c0060(&work->textLayers[1], 0, 4, 5, 0, label);
        Text_UploadTileBuffer(&work->textLayers[1]);
        detail = func_ov027_020ba2c8(&work->views[2], work->selectedIndex);
        CallVirtualHandlerSlot1(&work->textLayers[2], 0);
        selected = work->selectedIndex;
        if (IsEntryFlagSet_020c22c4(0, selected) || IsEntryFlagSet_020c22c4(1, selected)) {
            func_ov093_020c00c4(&work->textLayers[2], 0, 6, 3, 0, detail);
        }
        Text_UploadTileBuffer(&work->textLayers[2]);
    }
    if (mode != 1 && mode != -1) {
        return;
    }
    label = func_ov027_020ba2c8(titleView, 2);
    CallVirtualHandlerSlot1(&work->textLayers[3], 0);
    DrawShadowedAnchoredText_020c0060(&work->textLayers[3], 0, 4, 3, 0, label);
    Text_UploadTileBuffer(&work->textLayers[3]);

    nameView = &work->views[3];
    bar = &work->bars[1];
    lineHeight = GetNestedModeByte(&work->textLayers[4]);
    CallVirtualHandlerSlot1(&work->textLayers[4], 0);
    for (i = 0; i < 9; i++) {
        label = func_ov027_020ba2c8(nameView, work->entries[i + bar->scrollPos].nameIndex);
        DrawShadowedAnchoredText_020c0060(&work->textLayers[4], 0, i * (lineHeight + 6) + 4, 1, 0, label);
    }
    Text_UploadTileBuffer(&work->textLayers[4]);

    bar = &work->bars[1];
    lineHeight = GetNestedModeByte(&work->textLayers[5]);
    CallVirtualHandlerSlot1(&work->textLayers[5], 0);
    for (i = 0; i < 9; i++) {
        rowY = i * (lineHeight + 6);
        entry = &work->entries[i + bar->scrollPos];
        switch (entry->info->kind) {
        case 0:
            OS_SNPrintf_0202e094(text, 0x80, data_ov093_020c4d78, entry->value);
            break;
        case 1:
            OS_SNPrintf_0202e094(text, 0x80, data_ov093_020c4d80, entry->value);
            break;
        case 2:
            OS_SNPrintf_0202e094(text, 0x7f, data_ov093_020c4d88);
            break;
        }
        DrawShadowedAnchoredText_020c0060(&work->textLayers[5], 0x1c, rowY + 4, 1, 0x20, text);
    }
    Text_UploadTileBuffer(&work->textLayers[5]);
}





