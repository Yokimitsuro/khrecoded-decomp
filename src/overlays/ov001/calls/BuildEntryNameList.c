#include "nitro/types.h"

typedef struct {
    u16 recordId;
    u8 pad_02[6];
} EntryRef;

typedef struct {
    u8 pad_00[6];
    u16 count;
    EntryRef entries[1];
} EntryList;

typedef struct {
    u32 unk0;
    EntryList *list;
} EntrySource;

typedef struct {
    u8 pad_00[0x2c];
    u16 *name;
} RecordEntry;

typedef struct {
    u8 pad_000[0x10c];
    int nameCount;
    u16 **names;
} NameListOwner;

extern EntrySource *func_ov001_02073060(void);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern RecordEntry *GetRecordSlotPair1Entry(u32 recordId);
extern int Utf16Length(const u16 *str);
extern void Utf16CopyPadded(u16 *dest, const u16 *src, int length);

void BuildEntryNameList(NameListOwner *owner)
{
    EntryList *list = func_ov001_02073060()->list;
    int i;

    owner->nameCount = list->count;
    owner->names = NNSi_FndAllocFromDefaultHeap(list->count * sizeof(u16 *));
    for (i = 0; i < list->count; i++) {
        RecordEntry *entry = GetRecordSlotPair1Entry(list->entries[i].recordId);
        int length = Utf16Length(entry->name) + 1;
        owner->names[i] = NNSi_FndAllocFromDefaultHeap(length * sizeof(u16));
        Utf16CopyPadded(owner->names[i], entry->name, length);
    }
}
