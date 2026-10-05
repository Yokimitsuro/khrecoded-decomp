#include "nitro/types.h"
#include "nnsys/g2d.h"

typedef struct TextFrame {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 charBase;
    u16 palette;
    u16 hSpace;
    u16 vSpace;
} TextFrame;

typedef struct NameBaseTable {
    int baseIndex[11];
} NameBaseTable;

typedef struct FontSlot {
    NNSG2dFont font;
    void *file;
} FontSlot;

typedef struct TextWindow {
    u8 data[0x34];
} TextWindow;

typedef struct ListEntry {
    u16 recordId;
    u8 pad_02[6];
} ListEntry;

typedef struct ListData {
    u8 pad_00[6];
    u16 entryCount;
    ListEntry entries[1];
} ListData;

typedef struct ListRecord {
    u8 pad_00[4];
    ListData *data;
} ListRecord;

typedef struct NameEntry {
    u8 pad_00[0x40];
    u16 *name;
} NameEntry;

typedef struct DescEntry {
    u8 pad_00[0x28];
    u16 *text;
} DescEntry;

typedef struct WorldLocation {
    u8 world;
    u8 pad_01[0xd];
    u8 room;
} WorldLocation;

typedef struct SelectionRecord {
    u8 pad_00[0x10];
    WorldLocation location;
} SelectionRecord;

typedef struct HudContext {
    u8 pad_000[0x78];
    FontSlot labelFont;
    FontSlot narrowFont;
    u8 pad_090[0x18c - 0x90];
    TextWindow titleWindow;
    TextWindow listWindow;
    void **listLines;
    u8 pad_1f8[0xb34 - 0x1f8];
    u16 *names[0x200];
    u16 *currentName;
    ListRecord *listRecord;
} HudContext;

extern const TextFrame data_ov001_0209dc3c;
extern const NameBaseTable data_ov001_0209dd64;
extern void InitTextLayerAt(void *window, int bgLayer, void *charBase, NNSG2dFont *font, TextFrame *frame);
extern void AcquireRecordManager(void);
extern void ReleaseRecordManager(void);
extern int AcquireRecordSlot(int slot, int param);
extern BOOL ReleaseRecordSlot(s32 slot);
extern NameEntry *GetRecordSlotPair0Entry(s32 index);
extern DescEntry *GetRecordSlotPair1Entry(s32 index);
extern ListRecord *CloneRecord(ListRecord **out, u32 id, int useTailAlloc, int heapTag);
extern SelectionRecord *GetOverlaySelectionRecord(u32 selectionIndex);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern int Utf16Length(u16 *text);
extern u16 *Utf16CopyPadded(u16 *destination, u16 *source, int unitCount);
extern void *GetWord20(void *window);
extern void *func_02001928(void *window, int selectAsCurrent, int alignFromEnd);
extern void CallVirtualHandlerSlot1(void *window, int color);
extern void func_02001620(void *window, int x, int y, int color, int flags, const u16 *text, void *narrowFont, int maxWidth);

void LoadRecordNamesAndEntryList(HudContext *context)
{
    TextFrame frame = data_ov001_0209dc3c;
    NameBaseTable baseTable;
    ListData *list;
    NameEntry *entry;
    WorldLocation *location;
    int length;
    int i;
    u16 *text;

    InitTextLayerAt(&context->titleWindow, 3, 0, &context->labelFont.font, &frame);
    i = 0;
    AcquireRecordManager();
    AcquireRecordSlot(0, 1);
    do {
        entry = GetRecordSlotPair0Entry(i);
        length = Utf16Length(entry->name);
        context->names[i] = NNSi_FndAllocFromDefaultHeap((length + 1) * 2);
        Utf16CopyPadded(context->names[i], entry->name, length + 1);
        i++;
    } while (i < 0x200);
    ReleaseRecordSlot(0);
    baseTable = data_ov001_0209dd64;
    i = 0;
    location = &GetOverlaySelectionRecord(0)->location;
    context->currentName = context->names[baseTable.baseIndex[location->world] + location->room];
    AcquireRecordSlot(3, 1);
    CloneRecord(&context->listRecord, GetOverlaySelectionRecord(0)->location.world, 0, 0xe);
    ReleaseRecordSlot(3);
    list = context->listRecord->data;
    frame.x = 0;
    frame.y = 0xc;
    frame.width = 8;
    frame.height = 1;
    frame.charBase = 0x260;
    frame.palette = 7;
    InitTextLayerAt(&context->listWindow, 3, 0, &context->labelFont.font, &frame);
    context->listLines = NNSi_FndAllocFromDefaultHeap(list->entryCount * 4);
    AcquireRecordSlot(1, 1);
    for (; i < list->entryCount; i++) {
        if (i > 0) {
            context->listLines[i] = func_02001928(&context->listWindow, 1, 0);
        } else {
            context->listLines[i] = GetWord20(&context->listWindow);
        }
        text = GetRecordSlotPair1Entry(list->entries[i].recordId)->text;
        CallVirtualHandlerSlot1(&context->listWindow, 6);
        func_02001620(&context->listWindow, 4, 0, 4, 0x209, text, &context->narrowFont, 0x3c);
    }
    ReleaseRecordSlot(1);
    ReleaseRecordManager();
}
