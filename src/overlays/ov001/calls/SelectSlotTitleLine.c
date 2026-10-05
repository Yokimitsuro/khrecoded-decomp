#include "nitro/types.h"

typedef struct TitleEntry {
    u8 pad_00[0x8];
    u16 lineIndex;
} TitleEntry;

typedef struct TitleTable {
    u32 size;
    u16 unk_04;
    u16 count;
    TitleEntry *entries[1];
} TitleTable;

typedef struct TitleRecord {
    u16 id;
    u16 unk_02;
    void *header;
    TitleTable *table;
    u32 unk_0C;
} TitleRecord;

typedef struct SaveSlots {
    u32 unk_00;
    u16 titleIds[1];
} SaveSlots;

typedef struct HudContext {
    u8 pad_000[0x1c];
    u8 recordPool[0x1c0 - 0x1c];
    u8 titleWindow[0x34];
    void **titleLines;
    u8 pad_1f8[0x1338 - 0x1f8];
    TitleRecord *titleRecord;
    s32 titleAnimFrame;
} HudContext;

extern SaveSlots *GetSelectionPackedValueBlock(void);
extern u32 func_ov001_0207b688(u32 slot);
extern void SelectListNodeOrFirst(void *window, void *line);
extern void Text_UploadTileBuffer(void *window);
extern void *FindActiveRecordById(void *pool, u32 recordId);
extern void func_ov027_020b8288(void *pool, void *record);

void SelectSlotTitleLine(HudContext *context, int slot)
{
    SaveSlots *slots = GetSelectionPackedValueBlock();
    TitleEntry *entry;
    u32 titleId;
    u16 lineIndex;

    if (slot < 1) {
        return;
    }
    titleId = func_ov001_0207b688(slot - 1);
    if (titleId == 0xffff) {
        entry = context->titleRecord->table->entries[slots->titleIds[slot - 1]];
    } else {
        entry = context->titleRecord->table->entries[titleId];
    }
    lineIndex = entry->lineIndex;
    context->titleAnimFrame = 1;
    SelectListNodeOrFirst(context->titleWindow, context->titleLines[lineIndex]);
    Text_UploadTileBuffer(context->titleWindow);
    func_ov027_020b8288(context->recordPool, FindActiveRecordById(context->recordPool, 0x39));
}
