#include "nitro/types.h"

typedef struct NNSFndList {
    void *headObject;
    void *tailObject;
    u16 numObjects;
    u16 offset;
} NNSFndList;

typedef struct ListItem {
    u8 pad_00[0x28];
    u16 flags;
} ListItem;

typedef struct EntryTable {
    u8 entries[0x3c];
} EntryTable;

typedef struct EntryOwner {
    u8 pad_00[0x348];
    u8 defaultEntry[4];
} EntryOwner;

typedef struct EntrySelector {
    u8 pad_00[0xac];
    EntryTable *primaryEntries;
    EntryOwner *owner;
    EntryTable *tertiaryEntries;
    NNSFndList itemList;
    u8 pad_c4[0xc];
    int primaryCount;
    int pad_d4;
    int itemCount;
    int tertiaryCount;
    u8 pad_e0[0x24];
    int mode;
} EntrySelector;

extern ListItem *FND_GetListObjectByIndex(NNSFndList *list, u16 index);
extern ListItem *NNS_FndGetNextListObject(NNSFndList *list, ListItem *object);
extern ListItem *NNS_FndGetPrevListObject(NNSFndList *list, ListItem *object);

void *CycleMenuEntry(EntrySelector *selector, int index, int direction, int *outIndex)
{
    void *entry;
    int count;
    int step;
    int last;

    entry = NULL;
    switch (selector->mode) {
    case 0:
        count = selector->primaryCount;
        switch (direction) {
        case 0:
            index = (index + 1) % count;
            break;
        case 1:
            break;
        case 2:
            index = (index + count - 1) % count;
            break;
        }
        entry = &selector->primaryEntries[index];
        break;
    case 1:
        count = selector->itemCount;
        switch (direction) {
        case 0:
            entry = FND_GetListObjectByIndex(&selector->itemList, (index + 1) % count);
            for (step = 1; step <= count; step++) {
                if (entry == NULL) {
                    entry = NNS_FndGetNextListObject(&selector->itemList, NULL);
                }
                if ((((ListItem *)entry)->flags & 8) == 0) {
                    index = (index + step) % count;
                    break;
                }
                entry = NNS_FndGetNextListObject(&selector->itemList, entry);
            }
            if (step == count) {
                entry = NULL;
            }
            break;
        case 1:
            if (count > 0) {
                entry = FND_GetListObjectByIndex(&selector->itemList, index);
            }
            break;
        case 2:
            last = index + count;
            entry = FND_GetListObjectByIndex(&selector->itemList, (last - 1) % count);
            for (step = 1; step <= count; step++) {
                if (entry == NULL) {
                    entry = NNS_FndGetPrevListObject(&selector->itemList, NULL);
                }
                if ((((ListItem *)entry)->flags & 8) == 0) {
                    index = (last - step) % count;
                    break;
                }
                entry = NNS_FndGetPrevListObject(&selector->itemList, entry);
            }
            if (step == count) {
                entry = NULL;
            }
            break;
        }
        if (entry == NULL) {
            entry = selector->owner->defaultEntry;
        }
        break;
    case 2:
        count = selector->tertiaryCount;
        switch (direction) {
        case 0:
            index = (index + 1) % count;
            break;
        case 1:
            break;
        case 2:
            index = (index + count - 1) % count;
            break;
        }
        entry = &selector->tertiaryEntries[index];
        break;
    }
    if (outIndex != NULL) {
        *outIndex = index;
    }
    return entry;
}
