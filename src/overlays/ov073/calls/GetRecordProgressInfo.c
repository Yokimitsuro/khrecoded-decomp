#include "nitro/types.h"

typedef struct RecordEntry {
    u32 id;
    u8 pad_04[0x1c];
    u16 required;
    u8 pad_22[2];
    u8 hasCounter;
    u8 pad_25[3];
    u32 iconId;
    u32 nameId;
} RecordEntry;

typedef struct RecordProgressInfo {
    u32 id;
    u32 iconId;
    u32 nameId;
    u16 countText[8];
    BOOL complete;
} RecordProgressInfo;

typedef struct StatusMenu {
    u8 pad_0000[0x11dc];
    const char *countFormat;
} StatusMenu;

extern RecordEntry *GetRecordSlotPair1Entry(int recordId);
extern int OS_SNPrintf_0202e094(void *dst, u32 len, const char *fmt, ...);

void GetRecordProgressInfo(StatusMenu *menu, int recordId, int count, RecordProgressInfo *info)
{
    RecordEntry *entry = GetRecordSlotPair1Entry(recordId);

    info->id = entry->id;
    info->iconId = entry->iconId;
    info->nameId = entry->nameId;
    if (entry->hasCounter) {
        OS_SNPrintf_0202e094(info->countText, 7, menu->countFormat, count);
        info->complete = count >= entry->required;
        return;
    }
    info->countText[0] = 0;
    info->complete = FALSE;
}
