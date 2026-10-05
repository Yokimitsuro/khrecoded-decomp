#include "nitro/types.h"

typedef struct ItemRecord {
    u16 active;
    u16 pad_02;
    u16 recordIndex;
} ItemRecord;

typedef struct ItemPicker {
    u8 pad_0000[0xc];
    u8 keepRecord;
    u8 pad_000d[0x3c18 - 0xd];
    ItemRecord *records[1];
    u8 pad_3c1c[0x4d86 - 0x3c1c];
    s16 selected;
    u8 pad_4d88[0x7f9c - 0x4d88];
    int state;
} ItemPicker;

extern void ReleaseRecordEntry(int index);
extern BOOL ClearBg1AndRedraw(ItemPicker *picker);

void DiscardSelectedItem(ItemPicker *picker)
{
    if (picker->keepRecord == 0) {
        ItemRecord *record = picker->records[picker->selected];
        record->active = 0;
        ReleaseRecordEntry(record->recordIndex);
    }
    picker->state = 4;
    ClearBg1AndRedraw(picker);
}