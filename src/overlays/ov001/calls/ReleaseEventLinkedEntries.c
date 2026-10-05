#include "nitro/types.h"

typedef struct StageEntry {
    u8 pad_00[0xa];
    u16 eventId;
    u16 groupId;
} StageEntry;

typedef struct StageManager {
    u8 pad_00000[0x18d88];
    void *linkedEntryList;
} StageManager;

extern StageManager *func_ov001_0209c3e8(void);
extern void *func_ov001_0208f2a4(void *list);
extern StageEntry *func_ov001_0208f290(void *list, void *node);
extern void *func_ov001_0208f2b4(void *node);
extern void *GetStageActor(s16 groupId);
extern u8 *GetStageEventRecord(u32 id);
extern u16 GetSmallRecordIndex(StageEntry *entry);
extern void ReleaseStageSlotEntry(int listIndex, u16 entryId);

void ReleaseEventLinkedEntries(u8 *eventRecord)
{
    StageManager *manager = func_ov001_0209c3e8();
    void *node = func_ov001_0208f2a4(manager->linkedEntryList);

    while (node != NULL) {
        StageEntry *entry = func_ov001_0208f290(manager->linkedEntryList, node);
        u8 *record;

        node = func_ov001_0208f2b4(node);
        if (entry->groupId != 0 && GetStageActor((s16)entry->groupId) != NULL && entry->eventId != 0) {
            record = GetStageEventRecord(entry->eventId);
            if (record != NULL && record == eventRecord) {
                ReleaseStageSlotEntry(4, GetSmallRecordIndex(entry));
            }
        }
    }
}
