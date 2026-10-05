#include "nitro/types.h"

typedef struct {
    u32 owner;
    int index;
    u32 active;
    u32 *state;
    u32 *altState;
    u8 pad_14[0xc];
} PaletteEntry;

extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern PaletteEntry *FindListObjectByIdSecondary(void *manager, int index);
extern void SetPendingFromTable(int index);
extern void ClearPendingWord(void);
extern u32 MakePaletteUploadParams210(u32 index, u32 owner);
extern u32 MakePaletteUploadParams160(u32 index, u32 owner);
extern int GetTimedEntryKey(int index, u32 owner);
extern void AcquireSharedRecordState(void *obj, s32 key, u32 initArg, u32 context);
extern void NNS_FndAppendListObject(void *list, void *obj);

PaletteEntry *AcquirePaletteEntry(u8 *manager, u8 *scene, int index, u32 owner) {
    u8 *record = *(u8 **)(scene + 0xc);
    u32 altArg = *(u32 *)(record + 0x228);
    u32 context = *(u32 *)(manager + 0x14) + 8;
    BOOL high = index >= 15;
    PaletteEntry *entry = FindListObjectByIdSecondary(manager, index);
    s32 key;
    if (entry == NULL) {
        entry = NNSi_FndAllocFromDefaultHeap(sizeof(PaletteEntry));
        entry->index = index;
        entry->owner = owner;
        SetPendingFromTable(0);
        if (high) {
            index -= 15;
            key = MakePaletteUploadParams160(index, owner);
        } else {
            key = MakePaletteUploadParams210(index, owner);
        }
        entry->state = NNSi_FndAllocFromDefaultHeap(0x2c);
        *entry->state = 0;
        AcquireSharedRecordState(entry->state, key, (u32)(record + 8), context);
        if (altArg != 0 && high) {
            int altKey = GetTimedEntryKey(index, owner);
            entry->altState = NULL;
            if (altKey != 0) {
                entry->altState = NNSi_FndAllocFromDefaultHeap(0x2c);
                *entry->altState = 0;
                AcquireSharedRecordState(entry->altState, altKey, altArg, context);
            }
        } else {
            entry->altState = NULL;
        }
        ClearPendingWord();
        entry->active = 1;
        NNS_FndAppendListObject(manager + 0x58, entry);
    }
    return entry;
}
