#include "nitro/types.h"

typedef struct {
    int group;
    int type;
    u8 pad_08[0x10];
    u16 cost;
} SlotRecord;

typedef struct {
    u8 pad_0[2];
    u16 low : 8;
    u16 high : 8;
} RecordEntry;

typedef struct {
    u16 count;
    u16 value;
    s16 id;
    u16 pad_06;
    SlotRecord *record;
} ListEntry;

typedef struct {
    ListEntry entries[0x5ca];
    u8 pad_4578[0x4582 - 0x4578];
    u8 ready;
    u8 pad_4583;
    u32 typeMask;
} EntryList;

typedef struct {
    u8 pad_0000[0x28d4];
    s8 chapter;
    u8 pad_28d5[3];
    u8 owned[0x395];
    s8 links[200];
    u8 pad_2d35[0x2d84 - 0x2d35];
    u16 pairs[16];
    u8 pad_2da4[0x10];
    u16 extraA;
    u16 extraB;
    u16 extras[4];
    u32 amounts[8];
} SaveData;

extern SaveData *data_0205fe0c;
extern SlotRecord *GetRecordSlotPair0Entry(s32 index);
extern RecordEntry *GetActiveRecordEntryOrNull(u16 index);
extern u32 ReadGlobalPackedBits(u32 bitOffset, u32 bitCount);

static inline BOOL IsChapterRecordAvailable(int id, int chapter, int progress)
{
    switch (id) {
    case 0x160:
    case 0x161:
    case 0x178:
    case 0x179:
    case 0x17a:
    case 0x17b:
    case 0x17c:
    case 0x17d:
    case 0x17e:
    case 0x17f:
    case 0x180:
    case 0x181:
    case 0x182:
    case 0x183:
    case 0x184:
    case 0x185:
    case 0x186:
    case 0x19c:
    case 0x19d:
    case 0x19e:
    case 0x19f:
    case 0x1a0:
    case 0x1a1:
    case 0x1a2:
    case 0x1a3:
    case 0x1a4:
    case 0x1a5:
    case 0x1a6:
    case 0x1a7:
    case 0x1a8:
    case 0x1a9:
    case 0x1aa:
    case 0x1ab:
    case 0x1ac:
    case 0x1ad:
        return TRUE;
    case 0x164:
        return chapter == 1 && progress < 2;
    case 0x168:
    case 0x169:
    case 0x16a:
    case 0x16b:
    case 0x16c:
    case 0x16d:
    case 0x16e:
    case 0x16f:
    case 0x170:
    case 0x171:
    case 0x172:
    case 0x173:
    case 0x174:
    case 0x175:
    case 0x176:
    case 0x177:
        return chapter == 2 && progress < 2;
    case 0x188:
        return chapter == 5 && progress < 2;
    case 0x18c:
    case 0x18d:
    case 0x18e:
    case 0x18f:
    case 0x190:
    case 0x191:
    case 0x192:
    case 0x194:
        return chapter == 7 && progress < 2;
    }
    return FALSE;
}

void BuildRecordCountList_020c1994(EntryList *list)
{
    ListEntry *entry;
    s16 i;
    u8 *owned;
    s8 *links;
    RecordEntry *record;
    int group;
    int chapter;
    int progress;
    int k;
    u16 id;

    entry = list->entries;
    owned = data_0205fe0c->owned;
    links = data_0205fe0c->links;
    for (i = 0; i < 0x200; i++, entry++, owned++) {
        entry->record = GetRecordSlotPair0Entry(i);
        if ((i < 0 || i > 0x7f) && *owned != 0 && entry->record->cost < 9999) {
            if (entry->record->type == 10) {
                chapter = data_0205fe0c->chapter;
                progress = ReadGlobalPackedBits(0x1a00, 2);
                if (!IsChapterRecordAvailable(i, chapter, progress)) {
                    goto next;
                }
            }
            list->typeMask |= 1 << entry->record->type;
            entry->count = *owned;
            entry->value = 0;
        }
    next:
        entry->id = -1;
    }
    for (i = 0; i < 600; i++, entry++) {
        record = GetActiveRecordEntryOrNull(i);
        entry->count = 1;
        entry->value = 0;
        entry->id = i;
        if (record != NULL) {
            entry->record = GetRecordSlotPair0Entry((u8)record->high);
        } else {
            entry->record = NULL;
        }
        if (record != NULL && entry->record->cost < 9999) {
            list->typeMask |= 1 << entry->record->type;
            list->entries[entry->record->group].count++;
        }
    }
    for (i = 0; i < 200; i++, links++) {
        if (*links >= 0) {
            list->entries[*links + 0x90].value++;
        }
    }
    for (i = 0; i < 8; i++) {
        for (k = 0; k < 2; k++) {
            id = data_0205fe0c->pairs[i * 2 + k];
            if (id != 0xffff) {
                if (id < 0x200) {
                    list->entries[id].value += (u16)data_0205fe0c->amounts[i];
                } else {
                    group = list->entries[id].record->group;
                    list->entries[id].value++;
                    list->entries[group].value++;
                }
            }
        }
    }
    id = data_0205fe0c->extraA;
    if (id != 0xffff) {
        list->entries[id].value++;
    }
    id = data_0205fe0c->extraB;
    if (id != 0xffff) {
        list->entries[id].value++;
    }
    for (i = 0; i < 4; i++) {
        id = data_0205fe0c->extras[i];
        if (id != 0xffff) {
            list->entries[id].value++;
        }
    }
    list->typeMask |= (list->typeMask != 0) << 11;
    list->ready = 1;
}
