#include "nitro/types.h"

typedef struct StageRecordInfo {
    u16 unk_00;
    u16 isHidden : 1;
    u16 isFlagged : 1;
    u16 unk_02_2 : 14;
    u8 pad_04[0x20];
} StageRecordInfo;

typedef struct SlotTable {
    u8 pad_00[0x13e];
    s16 recordIds[8];
} SlotTable;

typedef struct SlotOwner {
    u8 pad_00[0x30];
    SlotTable *table;
} SlotOwner;

extern BOOL func_ov001_02087988(int id, StageRecordInfo *info);
extern BOOL StageRecord_IsDefeated(int id);

BOOL CanAddRecordToSlots(int id, SlotOwner *owner)
{
    StageRecordInfo info;
    SlotTable *table = owner->table;
    int slotIndex;

    for (slotIndex = 0; slotIndex < 8; slotIndex++) {
        if (id == table->recordIds[slotIndex]) {
            return FALSE;
        }
    }
    if (func_ov001_02087988(id, &info)) {
        if (!info.isHidden && !info.isFlagged && !StageRecord_IsDefeated(id)) {
            return TRUE;
        }
        return FALSE;
    }
    return FALSE;
}
