#include "nitro/types.h"

typedef struct HandleOwner {
    u8 pad0[2];
    u8 kind;
} HandleOwner;

typedef struct HandleEntry {
    HandleOwner *owner;
    int pad4;
    int key;
} HandleEntry;

typedef struct HandleGroup {
    HandleEntry *entries;
    HandleEntry *altEntries;
    int count;
    int altCount;
    u8 pad10[0x10];
} HandleGroup;

typedef struct HandleBank {
    u8 pad0[0xc];
    HandleGroup groups[2];
    u8 pad4c[0x14];
    HandleEntry *active;
} HandleBank;

extern BOOL IsObjHandleRequirementMet(HandleBank *bank, int group);
extern void BeginObjHandleCheck(HandleBank *bank, HandleEntry *entry, int group);

BOOL TriggerMatchingHandle(HandleBank *bank, int key, int group)
{
    int i;
    HandleEntry *entry;
    HandleEntry *entries;
    int count;
    HandleGroup *handles;
    BOOL found = FALSE;
    HandleGroup *groups = bank->groups;

    handles = &groups[group];
    entries = groups[group].entries;
    count = handles->count;

    if (IsObjHandleRequirementMet(bank, group)) {
        entries = handles->altEntries;
        count = handles->altCount;
    }
    for (i = 0; i < count; i++) {
        entry = &entries[i];
        if (key == entry->key && (bank->active == NULL || bank->active->owner->kind != entry->owner->kind)) {
            BeginObjHandleCheck(bank, entry, group);
            found = TRUE;
            break;
        }
    }
    return found;
}
