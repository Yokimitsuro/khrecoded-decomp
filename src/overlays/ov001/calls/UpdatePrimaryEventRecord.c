#include "nitro/types.h"

typedef struct EventRecord {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 pending;
    s32 handle;
} EventRecord;

typedef struct EventEntry {
    u32 unk_00;
    void *object;
    u8 pad_08[0x1c];
    u16 flags;
    u8 pad_26[0x2];
} EventEntry;

typedef struct EventContext {
    u32 unk_00;
    EventEntry entries[3];
    u8 pad_7C[0x60];
    EventRecord record;
} EventContext;

extern EventContext *data_ov001_020a04bc;
extern void func_ov001_0206d0ac(void *object);
extern void UpdateActorTargetLink(void *object, EventRecord *record);
extern BOOL UpdateTriggerWallContact(void *object, EventRecord *record);
extern void func_ov001_0206cdec(EventRecord *record, int extended);
extern void DropInactiveGroupMember(EventRecord *record);

void UpdatePrimaryEventRecord(void)
{
    EventContext *context = data_ov001_020a04bc;
    EventRecord *record = &context->record;
    EventEntry *entry = &context->entries[0];

    if ((entry->flags & 8) && (entry->flags & 0x14) <= 0 && record->pending == 0) {
        func_ov001_0206d0ac(entry->object);
        UpdateActorTargetLink(entry->object, record);
        if (!UpdateTriggerWallContact(entry->object, record)) {
            func_ov001_0206cdec(record, 0);
        }
        DropInactiveGroupMember(record);
    }
}
